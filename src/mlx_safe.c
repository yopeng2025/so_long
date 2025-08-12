/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_safe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:35:33 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/12 12:38:06 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#ifdef __linux__

void	mlx_loop_end_safe(void *mlx)
{
	if (mlx)
		mlx_loop_end(mlx);
}

void	destroy_display_safe(void *mlx)
{
	if (mlx)
		mlx_destroy_display(mlx);
}
#else

void	mlx_loop_end_safe(void *mlx)
{
	(void)mlx;
}

void	destroy_display_safe(void *mlx)
{
	(void)mlx;
}

#endif