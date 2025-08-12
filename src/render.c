/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:00:59 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/11 12:55:08 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define PLAYER_ANIM_DIV 50000
#define HUD_X 10
#define HUD_Y 10
#define HUD_COLOR 0xFFFFFF
#define HUD_LABEL "Moves:"

static void	draw_cell(t_game *g, int i, int j, int anim_frame);
static void	draw_map(t_game *g);
void		render(t_game *g);

void	load_textures(t_game *g)
{
	int	t_w;
	int	t_h;

	g->img_floor = mlx_xpm_file_to_image(g->mlx, "textures/floor.xpm",
			&g->tile_w, &g->tile_h);
	if (!g->img_floor)
		error_exit(g, "load floor.xpm failed");
	g->img_wall = mlx_xpm_file_to_image(g->mlx, "textures/wall.xpm", &t_w,
			&t_h);
	g->img_exit = mlx_xpm_file_to_image(g->mlx, "textures/exit.xpm", &t_w,
			&t_h);
	g->img_collect = mlx_xpm_file_to_image(g->mlx, "textures/collect.xpm", &t_w,
			&t_h);
	g->img_player[0] = mlx_xpm_file_to_image(g->mlx, "textures/player1.xpm",
			&t_w, &t_h);
	g->img_player[1] = mlx_xpm_file_to_image(g->mlx, "textures/player2.xpm",
			&t_w, &t_h);
	g->enemy.img[0] = mlx_xpm_file_to_image(g->mlx, "textures/enemy1.xpm", &t_w,
			&t_h);
	g->enemy.img[1] = mlx_xpm_file_to_image(g->mlx, "textures/enemy2.xpm", &t_w,
			&t_h);
	if (!g->img_wall || !g->img_exit || !g->img_collect || !g->img_player[0]
		|| !g->img_player[1] || !g->enemy.img[0] || !g->enemy.img[1])
		error_exit(g, "load .xpm failed");
}

static void	draw_cell(t_game *g, int i, int j, int anim_frame)
{
	size_t	len;
	char	c;

	c = '0';
	len = ft_strlen(g->map[j]);
	if (i < (int)len)
		c = g->map[j][i];
	mlx_put_image_to_window(g->mlx, g->win, g->img_floor, i * g->tile_w, j
		* g->tile_h);
	if (c == '1')
		mlx_put_image_to_window(g->mlx, g->win, g->img_wall, i * g->tile_w, j
			* g->tile_h);
	else if (c == 'C')
		mlx_put_image_to_window(g->mlx, g->win, g->img_collect, i * g->tile_w, j
			* g->tile_h);
	else if (c == 'E')
		mlx_put_image_to_window(g->mlx, g->win, g->img_exit, i * g->tile_w, j
			* g->tile_h);
	if (i == g->px && j == g->py)
		mlx_put_image_to_window(g->mlx, g->win, g->img_player[anim_frame], i
			* g->tile_w, j * g->tile_h);
	if (i == g->enemy.x && j == g->enemy.y)
		mlx_put_image_to_window(g->mlx, g->win, g->enemy.img[g->enemy.frame], i
			* g->tile_w, j * g->tile_h);
}

static void	draw_map(t_game *g)
{
	int	j;
	int	i;
	int	anim_frame;

	anim_frame = (g->frame / PLAYER_ANIM_DIV) % 2;
	j = 0;
	while (j < g->height)
	{
		i = 0;
		while (i < g->width)
		{
			draw_cell(g, i, j, anim_frame);
			i++;
		}
		j++;
	}
}

void	render(t_game *g)
{
	char	*count;
	char	*msg;

	draw_map(g);
	count = ft_itoa(g->moves);
	if (!count)
		error_exit(g, "itoa failed");
	msg = ft_strjoin(HUD_LABEL, count);
	free(count);
	if (!msg)
		error_exit(g, "strjoin failed");
	mlx_string_put(g->mlx, g->win, HUD_X, HUD_Y, HUD_COLOR, msg);
	free(msg);
}
