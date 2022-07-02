/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patrols_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 23:19:25 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/27 04:24:20 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	happy_peers(t_gl *gl, t_data lost)
{
	int	line;
	int	symb;

	line = -1;
	while (++line < gl->map.height)
	{
		symb = -1;
		while (gl->map.lenght > ++symb)
		{
			if (gl->map.body[line][symb] == 'C')
				mlx_put_image_to_window(gl->win.mlx, gl->win.win,
					gl->images.hp.img, symb * 50, line * 50);
		}
	}
}

int	death(t_gl *gl, int x, int y)
{
	t_data	lost;

	lost = putim(&gl->win, &gl->img, "img/lost.png");
	gl->map.status = -2;
	if (gl->map.orientation == 1)
		gl->images.plr_dead = putim(&gl->win, &gl->img, "img/dpr.png");
	else
		gl->images.plr_dead = putim(&gl->win, &gl->img, "img/dpl.png");
	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->images.plr_dead.img, gl->map.p_x * 50, gl->map.p_y * 50);
	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->images.patr.img, (gl->map.p_x + x) * 50, (gl->map.p_y + y) * 50);
	happy_peers(gl, lost);
	death_walls(gl, lost);
	return (1);
}

int	check_if_patrol(t_gl *gl, int x, int y, int ptrls)
{
	while (gl->map.pt_n > ptrls)
	{
		if (gl->map.p_y + y == gl->map.ptr[0][ptrls] &&
			gl->map.p_x + x == gl->map.ptr[1][ptrls])
			return (death(gl, x, y));
				ptrls++;
	}
	return (0);
}

void	patrols(t_vars *win, t_map *map, t_images *images, int volume)
{
	int		line;
	int		symb;

	line = -1;
	while (++line < map->height)
	{
		symb = -1;
		while (map->lenght > ++symb)
		{
			if (map->body[line][symb] == '0' && map->pt_n < PATROLS)
			{
				volume++;
				if (volume > DENSITY)
				{
					mlx_put_image_to_window(win->mlx, win->win,
						images->patr.img, symb * 50, line * 50);
					map->ptr[0][map->pt_n] = line;
					map->ptr[1][map->pt_n++] = symb;
					volume *= 0;
				}
			}
		}
	}
}
