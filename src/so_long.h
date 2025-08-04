#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h> // file attributes && permissions: mkdir() stat() ...
# include <sys/types.h>// data types in system calls: size_t pid_t ...

typedef struct s_enemy
{
	int		x, y, dir;  // position & direction(1:right -1:left)
	int		frame;
	void	*img[2];    // 2 frames of animation
}				t_enemy;

typedef struct s_game
{
	void	*mlx;       // handle of MLX
	void	*win;		// handle of windows(display content)
	char	**map;      //array
	int		width;      //map width
	int		height;
	int		tile_w;		//width/height of a single texture (pixels)
	int		tile_h;
	int		px;         //player position
	int		py;
	int		exit_x, exit_y; 
	int		collectibles;
	int		moves;
	int		frame;

	void	*img_wall;
	void	*img_floor;
	void	*img_exit;
	void	*img_collect;
	void	*img_player[2];// 2 frames for walking
	t_enemy	enemy;
}				t_game;

//utils
void	error_exit(char *msg);
int		close_window(void *param);
char	*read_file(char *path);
char	**split_lines(char *s, int *lines);

//map
char	**parse_map(char *path, t_game *g);
void	check_map(t_game *g);
void	verify_path(t_game *g);

//render
void	load_textures(t_game *g);
void	render(t_game *g);

//events
int	handle_key(int key, t_game *g);
int	update_loop(t_game *g);
//void move_enemy(t_game *g);

#endif
