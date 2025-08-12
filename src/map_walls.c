/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 11:47:56 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/08 11:52:03 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_top_bottom(char **map, t_game *g);
static void	check_sides(char **map, t_game *g);

static void	check_top_bottom(char **map, t_game *g)
{
	int	x;

	x = 0;
	while (x < g->width)
	{
		if (map[0][x] != '1' || map[g->height - 1][x] != '1')
			error_exit(g, "Map must be enclosed by walls");
		x++;
	}
}

static void	check_sides(char **map, t_game *g)
{
	int	y;

	y = 0;
	while (y < g->height)
	{
		if (map[y][0] != '1' || map[y][g->width - 1] != '1')
			error_exit(g, "Map must be enclosed by walls");
		y++;
	}
}

void	check_walls(char **map, t_game *g)
{
	check_top_bottom(map, g);
	check_sides(map, g);
}
