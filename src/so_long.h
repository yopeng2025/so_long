/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:53:39 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/12 12:38:38 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_enemy
{
	int		x;
	int		y;
	int		dir;
	int		frame;
	void	*img[2];
}			t_enemy;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	int		tile_w;
	int		tile_h;
	int		px;
	int		py;
	int		exit_x;
	int		exit_y;
	int		collectibles;
	int		moves;
	int		frame;
	void	*img_wall;
	void	*img_floor;
	void	*img_exit;
	void	*img_collect;
	void	*img_player[2];
	t_enemy	enemy;
}			t_game;

// close_window
void		error_exit(t_game *g, char *msg);
int			close_window(void *param);
void		game_over(t_game *g, char *msg);

// move
void		print_moves(t_game *g);

// map
char		**parse_map(char *path, t_game *g);
void		verify_path(t_game *g);
void		check_walls(char **map, t_game *g);

// render
void		load_textures(t_game *g);
void		render(t_game *g);

// events
int			handle_key(int key, t_game *g);
int			update_loop(t_game *g);
void		move_enemy(t_game *g);

// free
void		free_map(char **map, int height);
void		free_mlx(t_game *g);
void		clean_exit(t_game *g, int code);

// mlx_save
void		mlx_loop_end_safe(void *mlx);
void		destroy_display_safe(void *mlx);

// free_extra
void		destroy_all_images(t_game *g);
void		destroy_window_if_any(t_game *g);

// read_file
char		*read_file(t_game *g, const char *path);

// split_lines
char		**split_lines(char *s, int *out_lines, t_game *g);

#endif
