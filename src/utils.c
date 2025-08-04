/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:01:15 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/04 16:27:50 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(char *msg)
{
	write(2, "Error\n", 6);
	if(errno != 0)
		perror(msg);         //print error -> msg + errorNo.(error info)
	else
		fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);      //EXIT_FAILURE: 1, fails & exit
}
//Error
//open: No such file or directory

int	close_window(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);	
}

char	*read_file(char *path)
{
	struct	stat st;          //st.st_size for file size (unit: byte) included in struct stat in <sys/stat.h>
	char	*buff;
	int		fd;

	if(stat(path, &st) < 0)   // if file size < 0
		error_exit("stat");   // <sys/stat.h> stat() -> file metadata (size, creat time, permission ...)

	buff = malloc(st.st_size + 1);
	if(!buff)
		error_exit("malloc");
	fd = open(path, O_RDONLY);// 0stdin 1stdout 2stderr open-> 3/4   -> <0 error (errno specific no.)
	if(fd < 0)
		error_exit("open");
	if(read(fd, buff, st.st_size) != st.st_size) // read() save content to buff & return bytes been read
		error_exit("read");
	
	buff[st.st_size] = '\0';
	close(fd);
	return buff;
}

static int	count_lines(char *s)
{
	int	count = 0;

	while(*s)
	{
		if(*s == '\n')
			count++;
		s++;
	}
	return(count + 1);
}

//char *s = “line1\nline2\nline3”
//char **split_lines = {"line1", "line2", "line3", NULL};
char	**split_lines(char *s, int *out_lines)
{
	int		lines = count_lines(s);
	int		i = 0;
	char	**arr;
	char	*start;
	char	*endofline;

	arr = malloc(sizeof(char *) * (lines + 1)); //1 place for NULL
	start = s;

	while (i < lines)
	{
		endofline = start;
		while(*endofline && *endofline != '\n')
			endofline++;
		arr[i] = strndup(start, endofline - start);
		if (!arr[i])
			error_exit("strndup");
		start = *endofline ? endofline + 1 : endofline; // endofline ='\n' : endofline ='\0'
		i++;
	}
	arr[lines] = NULL;
	if (out_lines)                                      //If caller provided a int pointer, store the number of lines.
		*out_lines = lines;
	return arr;
}
