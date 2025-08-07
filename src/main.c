/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:01:42 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/07 14:42:39 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	g;

	g.moves = 0;
	g.frame = 0;
	g.map = NULL;
	g.mlx = NULL;
	g.win = NULL;
	if (ac != 2)
		error_exit(&g, "Usage: ./so_long map.ber");
	g.map = parse_map(av[1], &g);
	g.mlx = mlx_init();
	if (!g.mlx)
		error_exit(&g, "mlx_init");
	load_textures(&g);
	g.win = mlx_new_window(g.mlx, g.width * g.tile_w, g.height * g.tile_h,
			"so_long");
	g.enemy.x = g.exit_x;
	if (g.exit_y > 0 && g.map[g.exit_y - 1][g.exit_x] != '1')
		g.enemy.y = g.exit_y - 1;
	else
		g.enemy.y = g.exit_y + 1;
	g.enemy.dir = 1;
	mlx_key_hook(g.win, handle_key, &g);
	mlx_hook(g.win, 17, 0, close_window, &g);
	mlx_loop_hook(g.mlx, update_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}
