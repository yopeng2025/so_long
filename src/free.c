/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:10:31 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/11 19:40:01 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_mlx(t_game *g)
{
	if (!g || !g->mlx)
		return ;
	mlx_loop_end_safe(g->mlx);
	destroy_all_images(g);
	destroy_window_if_any(g);
	destroy_display_safe(g->mlx);
	free(g->mlx);
	g->mlx = NULL;
}

void	clean_exit(t_game *g, int code)
{
	if (g)
	{
		free_map(g->map, g->height);
		g->map = NULL;
		free_mlx(g);
	}
	exit(code);
}
