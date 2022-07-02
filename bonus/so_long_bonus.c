/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:27:39 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/28 02:35:47 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	destroy(t_map *map)
{
	while ((map->height)--)
		free(map->body[map->height]);
	free(map->body);
}

void	destroy_global(t_gl *gl, int flag)
{
	if (flag == 0)
	{
		destroy(&gl->map);
		free(gl);
		exit(0);
	}
	if (flag == 1)
	{
		destroy(&gl->map);
		free(gl);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	t_data		img;
	t_vars		win;
	t_map		map;
	t_images	images;

	if (argc == 2)
	{
		if (read_and_check_map(&map, argv[1]))
		{
			win.mlx = mlx_init();
			win.win = mlx_new_window(win.mlx, 50 * map.lenght, 50
					* map.height, "so_long");
			game(&win, &img, &map, &images);
		}
		else
		{
			destroy(&map);
			bug("Error\nMap is not valid.\n");
		}
	}
	else
		bug("Error\nWrong input.\n");
	return (0);
}
