/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:57:07 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/28 04:29:46 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	bug(char *s)
{
	printf("%s", s);
	exit(0);
	return (0);
}

int	fin(t_gl *gl)
{
	destroy_global(gl, 1);
	return (0);
}

void	death_walls(t_gl *gl, t_data lost)
{
	int	line;
	int	symb;

	line = -1;
	while (++line < gl->map.height)
	{
		symb = -1;
		while (gl->map.lenght > ++symb)
		{
			if (gl->map.body[line][symb] == '1')
				mlx_put_image_to_window(gl->win.mlx, gl->win.win,
					lost.img, symb * 50, line * 50);
		}
	}
	gl->map.status = -2;
	gl->done = 1;
}

void	fin_walls(t_gl *gl)
{
	int	line;
	int	symb;

	line = -1;
	while (++line < gl->map.height)
	{
		symb = -1;
		while (gl->map.lenght > ++symb)
		{
			if (gl->map.body[line][symb] == '1')
				mlx_put_image_to_window(gl->win.mlx, gl->win.win,
					gl->images.fin.img, symb * 50, line * 50);
			if (gl->map.body[line][symb] == 'E' && (line != gl->map.p_y
				&& symb != gl->map.p_y))
				mlx_put_image_to_window(gl->win.mlx, gl->win.win,
					gl->images.empty.img, symb * 50, line * 50);
		}
	}
	gl->map.status = -3;
	write(1, "You win!\n", 9);
}

void	draw_exits(t_gl *gl)
{
	int	line;
	int	symb;

	line = -1;
	while (++line < gl->map.height)
	{
		symb = -1;
		while (gl->map.lenght > ++symb)
		{
			if (gl->map.body[line][symb] == 'E')
				mlx_put_image_to_window(gl->win.mlx, gl->win.win,
					gl->images.exit.img, symb * 50, line * 50);
		}
	}
	gl->map.status = -69;
}
