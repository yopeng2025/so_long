/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:30:19 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/07 14:44:06 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

// move player to new position && outcomes
static void	move_player(int nx, int ny, t_game *g)
{
	char	c;

	c = g->map[ny][nx];
	if (c == '1')
		return ;
	if (nx == g->enemy.x && ny == g->enemy.y)
		error_exit(g, "You are caught by an enemy!");
	if (c == 'C')
	{
		g->collectibles--;
		g->map[ny][nx] = '0';
	}
	if (c == 'E')
	{
		if (g->collectibles == 0)
		{
			ft_printf("You win! Congratulations!\n");
			exit(EXIT_SUCCESS);
		}
		else
			return ;
	}
	g->px = nx;
	g->py = ny;
	g->moves++;
}

void	move_enemy(t_game *g)
{
	int	new_x;

	new_x = g->enemy.x + g->enemy.dir;
	/* Reverse direction if hitting a wall */
	if (new_x < 0 || new_x >= g->width || g->map[g->enemy.y][new_x] == '1')
	{
		g->enemy.dir *= -1;
		new_x = g->enemy.x + g->enemy.dir;
		/* Stay in place if reversing also hits a wall */
		if (new_x < 0 || new_x >= g->width || g->map[g->enemy.y][new_x] == '1')
			return ;
	}
	/* Check if enemy collides with player */
	if (new_x == g->px && g->enemy.y == g->py)
		error_exit(g, "You are caught by an enemy!");
	/* Update enemy position */
	g->enemy.x = new_x;
}

int	handle_key(int key, t_game *g)
{
	if (key == 65307) /*keycode = ESC*/
		error_exit(g, NULL);
	else if (key == 'W' || key == 'w' || key == 65362) /*↑*/
		move_player(g->px, g->py - 1, g);
	else if (key == 'S' || key == 's' || key == 65364) /*↓*/
		move_player(g->px, g->py + 1, g);
	else if (key == 'A' || key == 'a' || key == 65361) /*←*/
		move_player(g->px - 1, g->py, g);
	else if (key == 'D' || key == 'd' || key == 65363) /*→*/
		move_player(g->px + 1, g->py, g);
	return (0);
}

/*enemy movement && update map*/
int	update_loop(t_game *g)
{
	static int	enemy_anim_frame = 0;

	if (!g || !g->map)
		return (0);
	/* Update enemy movement and animation every 40000 frames */
	if (g->frame % 40000 == 0)
	{
		move_enemy(g);
		enemy_anim_frame = (enemy_anim_frame + 1) % 2;
		g->enemy.frame = enemy_anim_frame;
		render(g);
	}
	g->frame++;
	return (0);
}
