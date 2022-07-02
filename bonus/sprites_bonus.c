/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:43:23 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/28 02:38:39 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	imacs(t_gl *gl, int a)
{
	int		line;
	int		symb;

	line = -1;
	if (gl->map.status >= 0)
	{
		while (++line < gl->map.height)
		{
			symb = -1;
			while (gl->map.lenght > ++symb)
			{
				if (gl->map.body[line][symb] == '1' && ((!line && (symb
					&& symb != 1)) || line))
					mlx_put_image_to_window(gl->win.mlx, gl->win.win,
						(gl->imac.body[a].img), symb * 50, line * 50);
			}
		}
	}
}

int	sprites(t_gl *gl)
{
	char	*score;

	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->imac.score.img, 0, 0);
	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->imac.text.img, 50, 0);
	score = ft_itoa(gl->map.steps);
	mlx_string_put(gl->win.mlx, gl->win.win, 63, 24, 0x0000FF00, score);
	free(score);
	if (gl->map.status >= 0)
	{
		if (gl->map.orientation == 1)
			gl->images.plr = putim(&gl->win, &gl->img, "img/plr.png");
		if (gl->map.orientation == 0)
			gl->images.plr = putim(&gl->win, &gl->img, "img/plr-l.png");
		mlx_put_image_to_window(gl->win.mlx, gl->win.win,
			gl->images.empty.img, gl->map.p_x * 50, gl->map.p_y * 50);
		mlx_put_image_to_window(gl->win.mlx, gl->win.win,
			gl->images.plr.img, gl->map.p_x * 50, gl->map.p_y * 50);
	}
	usleep(100000);
	return (0);
}
