/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:01:59 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/13 18:40:55 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_count
{
	int		p;
	int		e;
}			t_count;

static void	check_map_shape(char **map, t_game *g);
static void	count_elements(t_game *g);
static void	handle_map_char(int x, int y, t_game *g, t_count *count);

char	**parse_map(char *path, t_game *g)
{
	char	*file;
	char	**map;

	file = read_file(g, path);
	map = split_lines(file, &g->height, g);
	free(file);
	if (!map || g->height <= 0 || !map[0])
		error_exit(g, "Empty map");
	g->width = ft_strlen(map[0]);
	g->map = map;
	check_map_shape(map, g);
	count_elements(g);
	check_walls(map, g);
	verify_path(g);
	return (map);
}

static void	check_map_shape(char **map, t_game *g)
{
	int		i;
	size_t	len;

	if (!map || g->height <= 0 || !map[0])
		error_exit(g, "Empty map");
	i = 0;
	while (i < g->height)
	{
		len = ft_strlen(map[i]);
		if (len == 0)
			error_exit(g, "Empty line in map");
		if ((int)len != g->width)
			error_exit(g, "Map must be rectangular");
		i++;
	}
}

static void	count_elements(t_game *g)
{
	int		x;
	int		y;
	t_count	count;

	if (!g->map || g->height <= 0 || g->width <= 0)
		error_exit(g, "Map dimensions not set");
	count.p = 0;
	count.e = 0;
	g->collectibles = 0;
	y = 0;
	while (y < g->height)
	{
		if (!g->map[y] || (int)ft_strlen(g->map[y]) < g->width)
			error_exit(g, "Map is not rectangular");
		x = 0;
		while (x < g->width)
		{
			handle_map_char(x, y, g, &count);
			x++;
		}
		y++;
	}
	if (count.p != 1 || count.e != 1 || g->collectibles < 1)
		error_exit(g, "Map must have 1 player, 1 exit and >=1 collectibles");
}

static void	handle_map_char(int x, int y, t_game *g, t_count *count)
{
	char	c;

	c = g->map[y][x];
	if (c == 'P')
	{
		count->p++;
		g->px = x;
		g->py = y;
	}
	else if (c == 'E')
	{
		count->e++;
		g->exit_x = x;
		g->exit_y = y;
	}
	else if (c == 'C')
		g->collectibles++;
	else if (c != '0' && c != '1')
		error_exit(g, "Invalid map character");
}
