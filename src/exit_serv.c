/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:30:51 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/27 04:08:16 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_serv(int line, int symb, t_gl *gl)
{
	mlx_put_image_to_window(gl->win.mlx, gl->win.win,
		gl->images.closed.img, symb * 50, line * 50);
	gl->map.e_x = symb;
	gl->map.e_y = line;
}
