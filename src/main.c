/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:01:42 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/04 16:28:11 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int ac, char **av)
{
    t_game  g;

    memset(&g, 0, sizeof(t_game));//Clear all fields to zero
    
    if(ac != 2)
        error_exit("Usage: ./so_long map.ber");
    g.moves = 0;
    g.frame = 0;
    g.map = parse_map(av[1], &g);
    g.mlx = mlx_init(); //Initialize MLX library and obtain graphics context
    if(!g.mlx)
        error_exit("mlx_init");
    //1. set tile_w && tile_h
    load_textures(&g);
    //2. create window (using tile_w && tile_h)
    g.win = mlx_new_window(g.mlx, g.width*g.tile_w, g.height*g.tile_h, "so_long");
    //3. confirm enemy position
    g.enemy.x = g.exit_x;
    if (g.exit_y > 0 && g.map[g.exit_y - 1][g.exit_x] != '1')
        g.enemy.y = g.exit_y - 1;
    else
        g.enemy.y = g.exit_y + 1;
    g.enemy.dir = 1;
    //4. event listening
    mlx_key_hook(g.win, handle_key, &g);
    mlx_hook(g.win, 17, 0, close_window, &g);//Event Listeners, 17:DestroyNotify/close windows 0:no mask -->use function error_exit
    mlx_loop_hook(g.mlx, update_loop, &g); //update game every frame
    mlx_loop(g.mlx); //listen && call update_loop && keep program running till exit
    return 0;
}
