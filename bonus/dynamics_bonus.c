/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamics_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 19:56:25 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/28 04:39:36 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	slack(t_gl *gl, int x, int y)
{
	gl->map.body[gl->map.p_y][gl->map.p_x] = '0';
	mlx_put_image_to_window(gl->win.mlx, gl->win.win, gl->images.plr.img,
		(gl->map.p_x + x) * 50, (gl->map.p_y + y) * 50);
	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->images.empty.img, gl->map.p_x * 50, gl->map.p_y * 50);
	gl->map.ex = 'E';
	if (gl->map.status == -69)
		gl->done = 1;
}

static void	killing(t_gl *gl, int x, int y)
{
	gl->map.body[gl->map.p_y + y][gl->map.p_x + x] = 'P';
	gl->map.body[gl->map.p_y][gl->map.p_x] = '0';
	gl->map.status += 1;
	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->images.empty.img, gl->map.p_x * 50, gl->map.p_y * 50);
	mlx_put_image_to_window(gl->win.mlx, gl->win.win, gl->images.plr.img,
		(gl->map.p_x + x) * 50, (gl->map.p_y + y) * 50);
	if (gl->map.ex == 'E')
	{
		gl->map.body[gl->map.p_y][gl->map.p_x] = 'E';
		mlx_put_image_to_window(gl->win.mlx, gl->win.win,
			gl->images.closed.img, gl->map.p_x * 50, gl->map.p_y * 50);
	}
	if (gl->map.ex == 'C')
		mlx_put_image_to_window(gl->win.mlx, gl->win.win,
			gl->images.dead_peer.img, gl->map.p_x * 50, gl->map.p_y * 50);
}

static void	empty_peer(t_gl *gl, char flag, int x, int y)
{
	if (flag == '0')
	{
		gl->map.body[gl->map.p_y + y][gl->map.p_x + x] = 'P';
		gl->map.body[gl->map.p_y][gl->map.p_x] = '0';
		if (gl->map.ex == '0' || gl->map.ex == 'P' || gl->map.ex == 'C')
			mlx_put_image_to_window(gl->win.mlx, gl->win.win,
				gl->images.empty.img, gl->map.p_x * 50, gl->map.p_y * 50);
		if (gl->map.ex == 'E')
			draw_exit_again(gl);
		if (gl->map.ex == 'C')
			mlx_put_image_to_window(gl->win.mlx, gl->win.win,
				gl->images.dead_peer.img, gl->map.p_x * 50, gl->map.p_y * 50);
		if (gl->map.orientation == 0)
			gl->images.plr = putim(&gl->win, &gl->img, "img/step-l.png");
		if (gl->map.orientation == 1)
			gl->images.plr = putim(&gl->win, &gl->img, "img/step-r.png");
		mlx_put_image_to_window(gl->win.mlx, gl->win.win,
			gl->images.plr.img, (gl->map.p_x + x) * 50, (gl->map.p_y
				+ y) * 50);
	}
	if (flag == 'C')
		killing(gl, x, y);
	gl->map.ex = flag;
}

static int	move(t_gl *gl, int x, int y, int ptrls)
{
	if (gl->map.body[gl->map.p_y + y][gl->map.p_x + x] != '1' &&
	(gl->map.status >= 0 || gl->map.status == -69))
	{
		if (gl->map.body[gl->map.p_y + y][gl->map.p_x + x] == '0')
		{
			if (check_if_patrol(gl, x, y, ptrls))
				return (1);
			empty_peer(gl, '0', x, y);
		}
		if (gl->map.body[gl->map.p_y + y][gl->map.p_x + x] == 'C')
			empty_peer(gl, 'C', x, y);
		if (gl->map.body[gl->map.p_y + y][gl->map.p_x + x] == 'E')
			slack(gl, x, y);
		else if (gl->map.ex == 'E')
			mlx_put_image_to_window(gl->win.mlx, gl->win.win,
				gl->images.closed.img, gl->map.p_x * 50, gl->map.p_y * 50);
		gl->map.p_x += x;
		gl->map.p_y += y;
		if (gl->map.status == gl->map.collectibles && !(gl->done))
			draw_exits(gl);
		return (1);
	}
	return (0);
}

int	going(t_gl *gl, int keycode, int orientation)
{
	if ((keycode == 0 || keycode == 1 || keycode == 2 || keycode == 13)
		&& (gl->map.status >= 0 || gl->map.status == -69))
	{
		imacs(gl, ((gl->map.steps) + 1) % 10);
		if (keycode == 0)
		{
			gl->map.orientation = 0;
			return (move(gl, -1, 0, 0));
		}
		if (keycode == 2)
		{
			gl->map.orientation = 1;
			return (move(gl, 1, 0, 0));
		}
		if (keycode == 1)
			return (move(gl, 0, 1, 0));
		if (keycode == 13)
			return (move(gl, 0, -1, 0));
	}
	return (0);
}
