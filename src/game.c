/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 00:45:32 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/27 03:59:34 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	key_hook(int keycode, t_gl *gl)
{
	if (gl == NULL)
		bug("Error\nCan't get memory.\n");
	if (going(gl, keycode))
	{
		(gl->map.steps)++;
		write(1, "Steps: ", 7);
		ft_putnbr(gl->map.steps, 1);
		write(1, "\n", 1);
	}
	if (keycode == 53)
		destroy_global(gl);
	if (gl->map.status == -1 && gl->done == 0)
	{
		mlx_put_image_to_window(gl->win.mlx, gl->win.win,
			gl->images.exit.img, gl->map.p_x * 50, gl->map.p_y * 50);
		fin_walls(gl);
	}
	return (0);
}

static void	pers(t_vars *win, t_map *map, t_images *images)
{
	int		line;
	int		symb;
	t_gl	*gl;

	gl = malloc(sizeof(t_gl));
	gl->map = *map;
	gl->win = *win;
	gl->images = *images;
	gl->done = 0;
	line = -1;
	while (++line < map->height)
	{
		symb = -1;
		while (map->lenght > ++symb)
		{
			if (map->body[line][symb] == 'P')
				mlx_put_image_to_window(win->mlx, win->win,
					images->plr.img, symb * 50, line * 50);
			if (map->body[line][symb] == 'E')
				exit_serv(line, symb, gl);
		}
	}
	mlx_key_hook(win->win, key_hook, gl);
	mlx_hook(win->win, 17, 0, fin, gl);
}

static t_data	putim(t_vars *win, t_data *img, char *path)
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
	images->dead_peer = putim(win, img, "img/dead-c.png");
	images->plr = putim(win, img, "img/plr.png");
	images->exit = putim(win, img, "img/exit.png");
	images->empty = putim(win, img, "img/empty.png");
	images->wall = putim(win, img, "img/wall.png");
	images->closed = putim(win, img, "img/closed.png");
	images->fin = putim(win, img, "img/fin.png");
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
	pers(win, map, images);
	mlx_loop(win->mlx);
}
