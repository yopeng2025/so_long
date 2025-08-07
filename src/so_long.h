/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:53:39 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/07 15:00:17 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include <sys/stat.h>  // file attributes && permissions: mkdir() stat() ...
# include <sys/types.h> // data types in system calls: size_t pid_t ...
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

// utils
void		error_exit(t_game *g, char *msg);
int			close_window(void *param);
void		free_mlx(t_game *g);
char		*read_file(t_game *g, char *path);
char		**split_lines(char *s, int *lines, t_game *g);

// map
char		**parse_map(char *path, t_game *g);
void		check_map(t_game *g);
void		verify_path(t_game *g);

// render
void		load_textures(t_game *g);
void		render(t_game *g);

// events
int			handle_key(int key, t_game *g);
int			update_loop(t_game *g);
void		move_enemy(t_game *g);

#endif
