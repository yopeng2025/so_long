/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:01:59 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/07 14:49:33 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

char	**parse_map(char *path, t_game *g)
{
	int		lines;
	char	*file;
	char	**map;
	int		i;
	size_t	len;
	int		e;
	int		y;
	int		x;
	char	c;
	int		x;
	int		p;

	file = read_file(g, path);
	map = split_lines(file, &lines, g);
	free(file);
	g->height = lines;
	g->width = ft_strlen(map[0]);
	i = 0;
	while (i < lines)
	{
		len = ft_strlen(map[i]);
		if (len == 0)
			error_exit(g, "Empty line in map");
		if ((int)len != g->width) /* prototype: int_t ft_strlen */
			error_exit(g, "Map must be rectangular");
		i++;
	}
	p = 0;
	e = 0;
	g->collectibles = 0;
	y = 0;
	while (y < g->height)
	{
		x = 0;
		while (x < g->width)
		{
			c = map[y][x];
			if (c == 'P')
			{
				g->px = x;
				g->py = y;
				p++;
			}
			else if (c == 'E')
			{
				g->exit_x = x;
				g->exit_y = y;
				e++;
			}
			else if (c == 'C')
				g->collectibles++;
			else if (c != '0' && c != '1')
				error_exit(g, "Invalid map character");
			x++;
		}
		y++;
	}
	if (p != 1 || e != 1 || g->collectibles < 1)
		error_exit(g, "Map must have 1 player, 1 exit and >1 collectibles");
	/* check borders */
	x = 0;
	while (x < g->width)
	{
		if (map[0][x] != '1' || map[g->height - 1][x] != '1')
			error_exit(g, "Map must be enclosed by walls");
		x++;
	}
	y = 0;
	while (y < g->height)
	{
		if (map[y][0] != '1' || map[y][g->width - 1] != '1')
			error_exit(g, "Map must be enclosed by walls");
		y++;
	}
	g->map = map;
	verify_path(g);
	return (map);
}

/* recursively search if player can reach every location */
static void	flood_fill(char **map, int x, int y, int height, int width, int *c,
		int *e)
{
	if (x < 0 || y < 0 || y >= height || x >= width)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'x')
		return ;
	if (map[y][x] == 'C')
		(*c)--;
	if (map[y][x] == 'E')
		(*e)--;
	map[y][x] = 'x';
	flood_fill(map, x + 1, y, height, width, c, e); // right
	flood_fill(map, x - 1, y, height, width, c, e); // left
	flood_fill(map, x, y + 1, height, width, c, e); // down
	flood_fill(map, x, y - 1, height, width, c, e); // up
}

void	verify_path(t_game *g)
{
	int	i;
	int	j;
	int	need_c;
	int	need_e;

	char **m; /* copy of map */
	m = malloc(sizeof(char *) * (g->height + 1));
	i = 0;
	while (i < g->height)
	{
		m[i] = ft_strdup(g->map[i]);
		i++;
	}
	m[g->height] = NULL;
	need_c = g->collectibles;
	need_e = 1;
	flood_fill(m, g->px, g->py, g->height, g->width, &need_c, &need_e);
	if (need_c != 0 || need_e != 0)
	{
		j = 0;
		while (j < g->height)
		{
			free(m[j]);
			j++;
		}
		free(m);
		error_exit(g, "Invalid path to all collectibles and exit");
	}
	i = 0;
	while (i < g->height)
	{
		free(m[i]);
		i++;
	}
	free(m);
}
