/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:03:45 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/11 12:04:57 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_all_images(t_game *g)
{
	void	*mlx;
	void	**imgs[8];
	int		i;

	if (!g || !g->mlx)
		return ;
	mlx = g->mlx;
	imgs[0] = (void **)&g->img_wall;
	imgs[1] = (void **)&g->img_floor;
	imgs[2] = (void **)&g->img_exit;
	imgs[3] = (void **)&g->img_collect;
	imgs[4] = (void **)&g->img_player[0];
	imgs[5] = (void **)&g->img_player[1];
	imgs[6] = (void **)&g->enemy.img[0];
	imgs[7] = (void **)&g->enemy.img[1];
	i = 0;
	while (i < 8)
	{
		if (*imgs[i])
		{
			mlx_destroy_image(mlx, *imgs[i]);
			*imgs[i] = NULL;
		}
		i++;
	}
}

void	destroy_window_if_any(t_game *g)
{
	if (!g || !g->mlx)
		return ;
	if (g->win)
	{
		mlx_destroy_window(g->mlx, g->win);
		g->win = NULL;
	}
}
