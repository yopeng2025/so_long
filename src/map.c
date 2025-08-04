/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:01:59 by yopeng            #+#    #+#             */
/*   Updated: 2025/08/04 18:13:19 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**parse_map(char *path, t_game *g)
{
	int		lines;
	char	*file;
	char	**map;

	file = read_file(path);
	map = split_lines(file, &lines);
	free(file);

	g->height = lines;
	g->width = strlen(map[0]);
	int	i = 0;
	while(i < lines)
	{
		size_t len = strlen(map[i]);
		if(len == 0)
			error_exit("Empty line in map");
		if((int)len != g->width) //prototype: int_t strlen
			error_exit("Map must be rectangular");
		i++;
	}

	int	p = 0; //count player/exit
	int e = 0;
	g->collectibles = 0;
	int	y = 0;
	while(y < g->height)
	{
		int	x = 0;
		while(x < g->width)
		{
			char c = map[y][x];
			if(c == 'P')
				{
					g->px = x;
					g->py = y;
					p++;
				}
			else if(c == 'E')
			{
				g->exit_x = x;
				g->exit_y = y;
				e++; 
			}
			else if(c == 'C')
				g->collectibles++;
			else if(c != '0' && c != '1')
				error_exit("Invalid map character");
			x++;
		}
		y++;
	}
	if(p !=1 || e != 1 || g->collectibles < 1)
		error_exit("Map must have 1 player, 1 exit and >1 collectibles");
	//check borders
	int	x = 0;
	while(x < g->width)
	{
		if(map[0][x] != '1' || map[g->height-1][x] != '1')
			error_exit("Map must be enclosed by walls");
		x++;
	}
	y = 0;
	while(y < g->height)
	{
		if(map[y][0] != '1' || map[y][g->width-1] != '1')
			error_exit("Map must be enclosed by walls");
		y++;
	}
	g->map = map;
	verify_path(g);
	//for (int y = 0; y < g->height; y++)
    //	printf("debug: line %d len=%zu content='%s'\n", y, strlen(g->map[y]), g->map[y]);
	return(map);
}

//recursively search if player can reach every location
static void	flood_fill(char **map, int x, int y, int height, int width, int *c, int *e)
{
	if(x < 0 || y < 0 || y >= height || x >= width)
		return;
	if(map[y][x] == '1' || map[y][x] == 'x') //wall / already check
		return;
	if(map[y][x] == 'C')
		(*c)--;
	if(map[y][x] == 'E')
		(*e)--;
	map[y][x] = 'x';
	flood_fill(map, x+1, y, height, width, c, e); //right
	flood_fill(map, x-1, y, height, width, c, e); //left
	flood_fill(map, x, y+1, height, width, c, e); //down
	flood_fill(map, x, y-1, height, width, c, e); //up
}

void	verify_path(t_game *g)
{
	char	**m; //copy of map
	int		i;
	int		j;
	
	m = malloc(sizeof(char *) * (g->height+1));//1 place for NULL
	i = 0;
	while(i < g->height)
	{
		m[i] = strdup(g->map[i]);
		i++;
	}
	m[g->height] = NULL;
	
	int	need_c = g->collectibles;
	int need_e = 1;
	flood_fill(m, g->px, g->py, g->height, g->width, &need_c, &need_e);
	if(need_c != 0 || need_e != 0)
	{
		j = 0;
		while(j < g->height)
		{
			free(m[j]);
			j++;
		}
		free(m);
		error_exit("Invalid path to all collectibles and exit");
	}
	i = 0;
	//free copy
	while(i < g->height)
	{
		free(m[i]);
		i++;
	}
	free(m);
}
