/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:57:07 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/27 15:33:55 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	bug(char *s)
{
	printf("%s", s);
	exit(0);
	return (0);
}

int	fin(t_gl *gl)
{
	destroy_global(gl);
	return (0);
}

void	ft_putnbr(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -1 * n;
	}
	if (n / 10)
		ft_putnbr(n / 10, fd);
	write(fd, &("0123456789"[n % 10]), 1);
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
	printf("You did it!\n");
	gl->done = 1;
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
}
