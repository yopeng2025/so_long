/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:01:15 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/12 12:15:38 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(t_game *g, char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	clean_exit(g, EXIT_FAILURE);
}

int	close_window(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	clean_exit(g, EXIT_SUCCESS);
	return (0);
}

void	game_over(t_game *g, char *msg)
{
	ft_putendl_fd(msg, 1);
	close_window(g);
}
