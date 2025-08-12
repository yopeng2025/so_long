/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:37:30 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/11 14:46:52 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_lines(const char *s);
static void	free_lines_partial(char **arr, int filled);
static char	*find_line_end(char *p);
static int	fill_one(char **arr, int idx, char **pstart);

static int	count_lines(const char *s)
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

static void	free_lines_partial(char **arr, int filled)
{
	int	k;

	if (!arr)
		return ;
	k = 0;
	while (k < filled)
	{
		free(arr[k]);
		k++;
	}
	free(arr);
}

static char	*find_line_end(char *p)
{
	char	*q;

	q = p;
	while (*q && *q != '\n')
		q++;
	return (q);
}

static int	fill_one(char **arr, int idx, char **pstart)
{
	char	*start;
	char	*end;

	start = *pstart;
	end = find_line_end(start);
	arr[idx] = ft_strndup(start, end - start);
	if (!arr[idx])
		return (0);
	if (*end)
		*pstart = end + 1;
	else
		*pstart = end;
	return (1);
}

char	**split_lines(char *s, int *out_lines, t_game *g)
{
	int		lines;
	int		i;
	char	**arr;
	char	*start;

	if (!s)
		error_exit(g, "split_lines: null input");
	lines = count_lines(s);
	arr = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!arr)
		error_exit(g, "malloc");
	i = 0;
	start = s;
	while (i < lines)
	{
		if (!fill_one(arr, i, &start))
			free_lines_partial(arr, i);
		i++;
	}
	arr[lines] = NULL;
	if (out_lines)
		*out_lines = lines;
	return (arr);
}
/*char *map = "111101111"*/
/*char **map = {"111", "101", "111"}*/