/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:59:57 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/11 14:19:34 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static off_t	get_size(t_game *g, const char *path)
{
	struct stat	st;

	if (stat(path, &st) < 0)
		error_exit(g, "stat");
	return (st.st_size);
}
/*Long integer variables specifically used to*/
/*hold file size and file offset*/

char	*read_file(t_game *g, const char *path)
{
	off_t	sz;
	char	*buf;
	int		fd;
	ssize_t	r;

	sz = get_size(g, path);
	buf = malloc((size_t)sz + 1);
	if (!buf)
		error_exit(g, "malloc");
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(buf);
		error_exit(g, "open");
	}
	r = read(fd, buf, (size_t)sz);
	if (r != sz)
	{
		free(buf);
		close(fd);
		error_exit(g, "read");
	}
	buf[sz] = '\0';
	close(fd);
	return (buf);
}
