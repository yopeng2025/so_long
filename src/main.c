/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:01:42 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/11 15:00:41 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_game_struct(t_game *g);
static void	init_mlx_and_window(t_game *g);
static void	init_enemy_position(t_game *g);
static void	setup_hooks_and_loop(t_game *g);

static void	init_game_struct(t_game *g)
{
	g->moves = 0;
	g->frame = 0;
	g->map = NULL;
	g->mlx = NULL;
	g->win = NULL;
	g->img_wall = NULL;
	g->img_floor = NULL;
	g->img_exit = NULL;
	g->img_collect = NULL;
	g->img_player[0] = NULL;
	g->img_player[1] = NULL;
	g->enemy.img[0] = NULL;
	g->enemy.img[1] = NULL;
	g->enemy.x = 0;
	g->enemy.y = 0;
	g->enemy.dir = 0;
}

static void	init_mlx_and_window(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		error_exit(g, "mlx_init");
	load_textures(g);
	g->win = mlx_new_window(g->mlx, g->width * g->tile_w, g->height * g->tile_h,
			"so_long");
	if (!g->win)
		error_exit(g, "mlx_new_window");
}

static void	init_enemy_position(t_game *g)
{
	g->enemy.x = g->exit_x;
	if (g->exit_y > 0 && g->map[g->exit_y - 1][g->exit_x] != '1')
		g->enemy.y = g->exit_y - 1;
	else
		g->enemy.y = g->exit_y + 1;
	g->enemy.dir = 1;
}

static void	setup_hooks_and_loop(t_game *g)
{
	mlx_key_hook(g->win, handle_key, g);
	mlx_hook(g->win, 17, 0, close_window, g);
	mlx_loop_hook(g->mlx, update_loop, g);
	mlx_loop(g->mlx);
}

int	main(int ac, char **av)
{
	t_game	g;

	init_game_struct(&g);
	if (ac != 2)
		error_exit(&g, "Usage: ./so_long map.ber");
	g.map = parse_map(av[1], &g);
	init_mlx_and_window(&g);
	init_enemy_position(&g);
	setup_hooks_and_loop(&g);
	return (0);
}
