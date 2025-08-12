/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:48:46 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/11 14:00:30 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_ffdata
{
	int		need_c;
	int		need_e;
	int		height;
	int		width;
}			t_ffdata;

static void	flood_fill(char **map, int x, int y, t_ffdata *d);
static char	**copy_map(t_game *g);
static void	free_map_copy(char **m, int height);

static void	flood_fill(char **map, int x, int y, t_ffdata *d)
{
	if (x < 0 || y < 0 || y >= d->height || x >= d->width)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'x')
		return ;
	if (map[y][x] == 'C')
		d->need_c--;
	if (map[y][x] == 'E')
		d->need_e--;
	map[y][x] = 'x';
	flood_fill(map, x + 1, y, d);
	flood_fill(map, x - 1, y, d);
	flood_fill(map, x, y + 1, d);
	flood_fill(map, x, y - 1, d);
}

static char	**copy_map(t_game *g)
{
	char	**m;
	int		i;

	m = (char **)malloc(sizeof(char *) * (g->height + 1));
	if (!m)
		error_exit(g, "malloc failed");
	i = 0;
	while (i < g->height)
	{
		m[i] = ft_strdup(g->map[i]);
		if (!m[i])
		{
			while (i > 0)
			{
				i--;
				free(m[i]);
			}
			free(m);
			error_exit(g, "strdup failed");
		}
		i++;
	}
	m[g->height] = NULL;
	return (m);
}

static void	free_map_copy(char **m, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(m[i]);
		i++;
	}
	free(m);
}

void	verify_path(t_game *g)
{
	char		**m;
	t_ffdata	d;

	d.need_c = g->collectibles;
	d.need_e = 1;
	d.height = g->height;
	d.width = g->width;
	m = copy_map(g);
	flood_fill(m, g->px, g->py, &d);
	free_map_copy(m, g->height);
	if (d.need_c != 0 || d.need_e != 0)
		error_exit(g, "Invalid path to all collectibles and exit");
}
