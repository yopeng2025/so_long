/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:01:15 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/07 15:08:53 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

void	error_exit(t_game *g, char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	free_mlx(g);
	exit(EXIT_FAILURE);
}

int	close_window(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	free_mlx(g);
	exit(EXIT_SUCCESS);
}

void	free_mlx(t_game *g)
{
	if (!g || !g->mlx)
		return ;
	if (g->img_wall)
		mlx_destroy_image(g->mlx, g->img_wall);
	if (g->img_floor)
		mlx_destroy_image(g->mlx, g->img_floor);
	if (g->img_exit)
		mlx_destroy_image(g->mlx, g->img_exit);
	if (g->img_collect)
		mlx_destroy_image(g->mlx, g->img_collect);
	if (g->img_player[0])
		mlx_destroy_image(g->mlx, g->img_player[0]);
	if (g->img_player[1])
		mlx_destroy_image(g->mlx, g->img_player[1]);
	if (g->enemy.img[0])
		mlx_destroy_image(g->mlx, g->enemy.img[0]);
	if (g->enemy.img[1])
		mlx_destroy_image(g->mlx, g->enemy.img[1]);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
}

char	*read_file(t_game *g, char *path)
{
	char		*buff;
	int			fd;
	struct stat	st;

	/* st.st_size for file size (unit: byte) sys/stat.h> */
	if (stat(path, &st) < 0)
		error_exit(g, "stat");
	buff = malloc(st.st_size + 1);
	if (!buff)
		error_exit(g, "malloc");
	fd = open(path, O_RDONLY); /* 0stdin 1stdout 2stderr open-> 3/4 */
	if (fd < 0)
		error_exit(g, "open");
	if (read(fd, buff, st.st_size) != st.st_size)
		/* read() save content to buff & return bytes been read */
		error_exit(g, "read");
	buff[st.st_size] = '\0';
	close(fd);
	return (buff);
}

static int	count_lines(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == '\n')
			count++;
		s++;
	}
	return (count + 1);
}

/* char *s = “line1\nline2\nline3” */
/* char **split_lines = {"line1", "line2", "line3", NULL} */
char	**split_lines(char *s, int *out_lines, t_game *g)
{
	int		lines = count_lines(s);
	int		i = 0;
	char	**arr;
	char	*start;
	char	*endofline;

	arr = malloc(sizeof(char *) * (lines + 1));
	start = s;
	while (i < lines)
	{
		endofline = start;
		while (*endofline && *endofline != '\n')
			endofline++;
		arr[i] = ft_strndup(start, endofline - start);
		if (!arr[i])
			error_exit(g, "ft_strndup");
		start = *endofline ? endofline + 1 : endofline;
		i++;
	}
	arr[lines] = NULL;
	/* If caller provided a int pointer */
	if (out_lines)
		store the number of lines.*out_lines = lines;
	return (arr);
}
