/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:30:19 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/04 18:18:38 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//move player to new position && outcomes
static void move_player(int nx, int ny, t_game *g)
{
    char    c = g->map[ny][nx];
    
    if(c == '1') 
        return;
    if(nx == g->enemy.x && ny == g->enemy.y)
        error_exit("You are caught by an enemy!");
    if(c == 'C')
    {
        g->collectibles--;
        g->map[ny][nx] = '0';
    }
    if(c == 'E')
    {
        if(g->collectibles == 0)
        {
            write(1, "🎉 You win! Congratulations!\n", 32);
            sleep(1);
            exit(EXIT_SUCCESS); // == return 0
        }
        else 
            return;
    }
    g->px = nx;
    g->py = ny;
    g->moves++;
}

void move_enemy(t_game *g)
{
    int new_x = g->enemy.x + g->enemy.dir;

    // 遇到边界或墙就反向
    if (new_x < 0 || new_x >= g->width || g->map[g->enemy.y][new_x] == '1')
    {
        g->enemy.dir *= -1;
        new_x = g->enemy.x + g->enemy.dir;
        // 如果反向也走不了，就原地不动
        if (new_x < 0 || new_x >= g->width || g->map[g->enemy.y][new_x] == '1')
            return;
    }
    // 检查敌人是否撞到玩家
    if (new_x == g->px && g->enemy.y == g->py)
        error_exit("You are caught by an enemy!");
    // 更新敌人位置
    g->enemy.x = new_x;
}

int handle_key(int key, t_game *g)
{
    if(key == 65307)        //keycode = ESC
        error_exit(NULL);
    else if(key == 'W' || key == 'w' || key == 65362) // ↑
        move_player(g->px, g->py-1, g);
    else if(key == 'S' || key == 's' || key == 65364) // ↓ 
        move_player(g->px, g->py+1, g);
    else if(key == 'A' || key == 'a' || key == 65361) // ←
        move_player(g->px-1, g->py, g);
    else if(key == 'D' || key == 'd' || key == 65363) // →
        move_player(g->px+1, g->py, g);
    return 0;
}

//enemy movement && update map
int update_loop(t_game *g)
{
    static int enemy_anim_frame = 0;   // 敌人当前动画帧

    if (!g || !g->map)
        return 0;
        
    if (g->frame % 40000 == 0)          //每10000帧渲染一次
    {
        move_enemy(g);
        enemy_anim_frame = (enemy_anim_frame + 1) % 2;
        g->enemy.frame = enemy_anim_frame;
        render(g);
    }    
    g->frame++;
    return 0;
}