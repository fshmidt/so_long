/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:45:32 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/28 04:32:15 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	key_hook(int keycode, t_gl *gl)
{
	if (gl == NULL)
		bug("Error\nCan't get memory.\n");
	if (going(gl, keycode, gl->map.orientation))
	{
		(gl->map.steps)++;
		write(1, "Steps: ", 7);
		ft_putnbr(gl->map.steps, 1);
		write(1, "\n", 1);
	}
	if (keycode == 53)
		destroy_global(gl, 1);
	if (gl->map.status == -69 && gl->done == 1)
	{
		mlx_put_image_to_window(gl->win.mlx, gl->win.win,
			gl->images.exit.img, gl->map.p_x * 50, gl->map.p_y * 50);
		fin_walls(gl);
	}
	if (gl->map.status == -2)
	{
		write(1, "You've lost!\n", 13);
		gl->map.status = -3;
	}
	return (0);
}

void	pers(t_gl *gl)
{
	int		line;
	int		symb;

	line = -1;
	while (++line < gl->map.height)
	{
		symb = -1;
		while (gl->map.lenght > ++symb)
		{
			if (gl->map.body[line][symb] == 'P')
				mlx_put_image_to_window(gl->win.mlx, gl->win.win,
					gl->images.plr.img, symb * 50, line * 50);
			if (gl->map.body[line][symb] == 'E')
				exit_serv(line, symb, gl);
		}
	}
	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->imac.score.img, 0, 0);
	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->imac.text.img, 50, 0);
}

t_data	putim(t_vars *win, t_data *img, char *path)
{
	int	a;
	int	b;

	img->img = mlx_png_file_to_image(win->mlx, path, &a, &b);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (*img);
}

static void	get_img(t_vars *win, t_data *img, t_images *images)
{
	images->collectibles = putim(win, img, "img/collectible.png");
	images->dead_peer = putim(win, img, "img/dph.png");
	images->hp = putim(win, img, "img/happy_peer.png");
	images->plr = putim(win, img, "img/plr.png");
	images->exit = putim(win, img, "img/exit.png");
	images->empty = putim(win, img, "img/empty.png");
	images->wall = putim(win, img, "img/wall.png");
	images->closed = putim(win, img, "img/closed.png");
	images->fin = putim(win, img, "img/fin.png");
	images->patr = putim(win, img, "img/patrol.png");
	images->step_l = putim(win, img, "img/step-l.png");
	images->step_r = putim(win, img, "img/step-r.png");
}

void	game(t_vars *win, t_data *img, t_map *map, t_images *images)
{
	int	line;
	int	symb;

	get_img(win, img, images);
	line = -1;
	while (++line < map->height)
	{
		symb = -1;
		while (map->lenght > ++symb)
		{
			if (map->body[line][symb] == '1')
				mlx_put_image_to_window(win->mlx, win->win,
					images->wall.img, symb * 50, line * 50);
			if (map->body[line][symb] == '0')
				mlx_put_image_to_window(win->mlx, win->win,
					images->empty.img, symb * 50, line * 50);
			if (map->body[line][symb] == 'C')
				mlx_put_image_to_window(win->mlx, win->win,
					images->collectibles.img, symb * 50, line * 50);
		}
	}
	map->steps = 0;
	patrols(win, map, images, 0);
	init_global_struct_and_hooks(win, map, images, img);
	mlx_loop(win->mlx);
}
