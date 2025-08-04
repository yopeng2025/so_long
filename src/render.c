/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:00:59 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/04 18:04:15 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    load_textures(t_game *g)
{
    g->img_floor = mlx_xpm_file_to_image(g->mlx, "textures/floor.xpm", &g->tile_w, &g->tile_h);
    if(!g->img_floor)
        error_exit("load floor.xpm failed");
    //do not change tile_w && tile_h
    int t_w, t_h;
    g->img_wall = mlx_xpm_file_to_image(g->mlx, "textures/wall.xpm", &t_w, &t_h);
        //debug: printf("wall size: %d x %d\n", t_w, t_h);
    g->img_exit = mlx_xpm_file_to_image(g->mlx, "textures/exit.xpm", &t_w, &t_h);
        //debug: printf("exit size: %d x %d\n", t_w, t_h);
    g->img_collect = mlx_xpm_file_to_image(g->mlx, "textures/collect.xpm", &t_w, &t_h);
        //debug: printf("collect size: %d x %d\n", t_w, t_h);
    g->img_player[0] = mlx_xpm_file_to_image(g->mlx, "textures/player1.xpm", &t_w, &t_h);
    g->img_player[1] = mlx_xpm_file_to_image(g->mlx, "textures/player2.xpm", &t_w, &t_h);
        //debug: printf("player size: %d x %d\n", t_w, t_h);
    g->enemy.img[0] = mlx_xpm_file_to_image(g->mlx, "textures/enemy1.xpm", &t_w, &t_h);  
    g->enemy.img[1] = mlx_xpm_file_to_image(g->mlx, "textures/enemy2.xpm", &t_w, &t_h);
        //debug: printf("enemy size: %d x %d\n", t_w, t_h);
    if(!g->img_wall || !g->img_exit || !g->img_collect ||
        !g->img_player[0] || !g->img_player[1] ||
        !g->enemy.img[0] || !g->enemy.img[1])
        error_exit("load .xpm failed");
}

//redrawing the game screen
void render(t_game *g)
{
    int     i, j;
    char    c;
    int     anim_frame;

    j = 0;
    while (j < g->height)
    {
        i = 0;
        while (i < g->width)
        {
            c = '0'; // 背景默认地板
            if (i < (int)strlen(g->map[j]))
                c = g->map[j][i];
            // 1. 背景：用地板覆盖，确保不会闪
            mlx_put_image_to_window(g->mlx, g->win, g->img_floor,
                                    i * g->tile_w, j * g->tile_h);
            // 2. 根据地图元素绘制内容
            if (c == '1')
                mlx_put_image_to_window(g->mlx, g->win, g->img_wall,
                                        i * g->tile_w, j * g->tile_h);
            else if (c == 'C')
                mlx_put_image_to_window(g->mlx, g->win, g->img_collect,
                                        i * g->tile_w, j * g->tile_h);
            else if (c == 'E')
                mlx_put_image_to_window(g->mlx, g->win, g->img_exit,
                                        i * g->tile_w, j * g->tile_h);
            // 3. 玩家动画（动画速度变慢：每 50000 帧切换一次图片）
            anim_frame = (g->frame / 50000) % 2;
            if (i == g->px && j == g->py)
                mlx_put_image_to_window(g->mlx, g->win,
                                        g->img_player[anim_frame],
                                        i * g->tile_w, j * g->tile_h);
            // 4. 敌人动画
            if (i == g->enemy.x && j == g->enemy.y)
                mlx_put_image_to_window(g->mlx, g->win,
                                        g->enemy.img[g->enemy.frame],
                                        i * g->tile_w, j * g->tile_h);
            i++;
        }
        j++;
    }
    // 5. 显示移动次数
    char buf[32];
    sprintf(buf, "Moves:%d", g->moves);
    mlx_string_put(g->mlx, g->win, 10, 10, 0xFFFFFF, buf);
}