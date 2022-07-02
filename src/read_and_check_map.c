/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_check_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:53:29 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/27 03:53:00 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	good_numbers(t_map *map)
{
	int	line;
	int	symb;

	line = 0;
	while (line < map->height)
	{
		symb = 0;
		while (map->lenght > symb)
		{
			if (map->body[0][symb] != '1' || map->body[line][0] != '1' ||
				map->body[line][map->lenght - 1] != '1' ||
				map->body[map->height - 1][symb] != '1')
				bug("Error\nWalls must be composed of only '1'.\n");
			if (map->body[line][symb] != '1' && map->body[line][symb] !=
				'0' && map->body[line][symb] != 'P' && map->body[line][symb]
				!= 'E' && map->body[line][symb] != 'C')
				bug("Error\nMap must be composed of P,C,E,1,0.\n");
				symb++;
		}
		line++;
	}
	return (1);
}

static int	check_map(t_map *map)
{
	int	line;
	int	symb;

	line = -1;
	while (++line < map->height)
	{
		symb = -1;
		while (map->lenght > ++symb)
		{
			if (map->body[line][symb] == 'P')
			{
				map->plr += 1;
				map->p_x = symb;
				map->p_y = line;
			}
			if (map->body[line][symb] == 'C')
				map->collectibles += 1;
			if (map->body[line][symb] == 'E')
				map->exit += 1;
		}
	}
	if (map->plr != 1 || map->collectibles < 1 || map->exit < 1
		|| !good_numbers(map))
		return (0);
	return (1);
}

static t_map	zero_map(void)
{
	t_map	map;

	map.x = 0;
	map.y = 0;
	map.plr = 0;
	map.collectibles = 0;
	map.exit = 0;
	map.lenght = 0;
	map.status = 0;
	map.ex = 'P';
	return (map);
}

static int	length_height(char *map_name, t_map *map, int checker)
{
	int		h;
	int		fd;
	char	*line;

	fd = open(map_name, O_RDONLY);
	line = get_next_line(fd);
	map->lenght = ft_strlen(line) - 1;
	h = 0;
	while (line != NULL)
	{
		h++;
		free(line);
		line = get_next_line(fd);
		if (line != NULL && ((map->lenght != ft_strlen(line) - 1
					&& line[ft_strlen(line) - 1] != '1') || (map->lenght
					== ft_strlen(line) - 1 && line[ft_strlen(line) - 1]
					!= '\n')))
				checker++;
	}
	if (checker == 1)
		bug("Error\nMap has curved edge.\n");
	close(fd);
	return (h);
}

int	read_and_check_map(t_map *map, char *map_name)
{
	int		fd;
	int		a;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		bug("Error\nCan't open file.\n");
	*map = zero_map();
	map->height = length_height(map_name, map, 0);
	map->body = (char **)malloc(sizeof(char *) * map->height);
	if (map->body == NULL)
		bug("Error\nCan't get memory.\n");
	a = 0;
	while (a < map->height)
		map->body[a++] = get_next_line(fd);
	return (check_map(map));
}
