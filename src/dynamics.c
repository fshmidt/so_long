/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:56:25 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/28 00:38:48 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	slack(t_gl *gl, int x, int y)
{
	gl->map.body[gl->map.p_y][gl->map.p_x] = '0';
	if (gl->map.status == gl->map.collectibles)
		gl->map.status = -1;
	mlx_put_image_to_window(gl->win.mlx, gl->win.win, gl->images.plr.img,
		(gl->map.p_x + x) * 50, (gl->map.p_y + y) * 50);
	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->images.empty.img, gl->map.p_x * 50, gl->map.p_y * 50);
	gl->map.ex = 'E';
}

static void	event(t_gl *gl, int flag, int x, int y)
{
	if (flag == 'C')
	{
		gl->map.body[gl->map.p_y + y][gl->map.p_x + x] = 'P';
		gl->map.body[gl->map.p_y][gl->map.p_x] = '0';
		gl->map.status += 1;
		mlx_put_image_to_window(gl->win.mlx, gl->win.win,
			gl->images.empty.img, gl->map.p_x * 50, gl->map.p_y * 50);
		mlx_put_image_to_window(gl->win.mlx, gl->win.win,
			gl->images.plr.img, (gl->map.p_x + x) * 50, (gl->map.p_y
				+ y) * 50);
	}
}

static void	empty_peer(t_gl *gl, int flag, int x, int y)
{
	if (flag == '0')
	{
		gl->map.body[gl->map.p_y + y][gl->map.p_x + x] = 'P';
		gl->map.body[gl->map.p_y][gl->map.p_x] = '0';
		if (gl->map.ex == '0' || gl->map.ex == 'P' || gl->map.ex == 'C')
			mlx_put_image_to_window(gl->win.mlx, gl->win.win,
				gl->images.empty.img, gl->map.p_x * 50, gl->map.p_y * 50);
		if (gl->map.ex == 'E')
		{
			mlx_put_image_to_window(gl->win.mlx, gl->win.win,
				gl->images.closed.img, gl->map.p_x * 50, gl->map.p_y * 50);
			gl->map.body[gl->map.p_y][gl->map.p_x] = 'E';
		}
		mlx_put_image_to_window(gl->win.mlx, gl->win.win,
			gl->images.plr.img, (gl->map.p_x + x) * 50, (gl->map.p_y
				+ y) * 50);
	}
	if (flag == 'C')
		event(gl, flag, x, y);
	gl->map.ex = flag;
}

static int	move(t_gl *gl, int x, int y)
{
	if (gl->map.body[gl->map.p_y + y][gl->map.p_x + x] != '1' &&
	gl->map.status >= 0)
	{
		if (gl->map.body[gl->map.p_y + y][gl->map.p_x + x] == '0')
			empty_peer(gl, '0', x, y);
		if (gl->map.body[gl->map.p_y + y][gl->map.p_x + x] == 'C')
			empty_peer(gl, 'C', x, y);
		if (gl->map.body[gl->map.p_y + y][gl->map.p_x + x] == 'E')
			slack(gl, x, y);
		else if (gl->map.ex == 'E')
			mlx_put_image_to_window(gl->win.mlx, gl->win.win,
				gl->images.closed.img, gl->map.p_x * 50, gl->map.p_y * 50);
		gl->map.p_x += x;
		gl->map.p_y += y;
		if (gl->map.status == gl->map.collectibles)
			draw_exits(gl);
		return (1);
	}
	return (0);
}

int	going(t_gl *gl, int keycode)
{
	if (keycode == 0)
		return (move(gl, -1, 0));
	if (keycode == 1)
		return (move(gl, 0, 1));
	if (keycode == 2)
		return (move(gl, 1, 0));
	if (keycode == 13)
		return (move(gl, 0, -1));
	return (0);
}
