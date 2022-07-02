/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_exit_serv_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:30:51 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/28 04:21:39 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	draw_exit_again(t_gl *gl)
{
	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->images.closed.img, gl->map.p_x * 50, gl->map.p_y * 50);
	gl->map.body[gl->map.p_y][gl->map.p_x] = 'E';
}

void	exit_serv(int line, int symb, t_gl *gl)
{
	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->images.closed.img, symb * 50, line * 50);
	gl->map.e_x = symb;
	gl->map.e_y = line;
}

static void	init_imac(t_gl *gl, t_imac *imac)
{
	imac->body[0] = putim(&gl->win, &gl->img, "img/comp1.png");
	imac->body[1] = putim(&gl->win, &gl->img, "img/comp2.png");
	imac->body[2] = putim(&gl->win, &gl->img, "img/comp3.png");
	imac->body[3] = putim(&gl->win, &gl->img, "img/comp4.png");
	imac->body[4] = putim(&gl->win, &gl->img, "img/comp5.png");
	imac->body[5] = putim(&gl->win, &gl->img, "img/comp6.png");
	imac->body[6] = putim(&gl->win, &gl->img, "img/comp7.png");
	imac->body[7] = putim(&gl->win, &gl->img, "img/comp8.png");
	imac->body[8] = putim(&gl->win, &gl->img, "img/comp9.png");
	imac->body[9] = putim(&gl->win, &gl->img, "img/comp10.png");
	imac->score = putim(&gl->win, &gl->img, "img/score.png");
	imac->text = putim(&gl->win, &gl->img, "img/text.png");
}

void	init_global_struct_and_hooks(t_vars *win, t_map *map, t_images
*images, t_data *img)
{
	t_gl	*gl;
	t_imac	imac;

	gl = (t_gl *)malloc(sizeof(t_gl));
	if (gl == NULL)
	{
		destroy(map);
		bug("Error\nCan't get memory.\n");
	}
	gl->map = *map;
	gl->win = *win;
	gl->images = *images;
	gl->img = *img;
	gl->done = 0;
	init_imac(gl, &imac);
	gl->imac = imac;
	pers(gl);
	mlx_string_put(gl->win.mlx, gl->win.win, 63, 24, 0x0000FF00, "0");
	mlx_loop_hook(win->mlx, sprites, gl);
	mlx_key_hook(win->win, key_hook, gl);
	mlx_hook(win->win, 17, 0, fin, gl);
}
