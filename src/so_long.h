/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:28:36 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/27 03:59:55 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_map
{
	int		lenght;
	int		height;
	int		x;
	int		y;
	int		steps;
	int		status;
	int		plr;
	int		orientation;
	int		p_x;
	int		p_y;
	int		ex;
	int		collectibles;
	int		exit;
	int		e_x;
	int		e_y;
	char	**body;
}				t_map;

typedef struct s_images
{
	t_data	plr;
	t_data	collectibles;
	t_data	exit;
	t_data	plr_right;
	t_data	dead_peer;
	t_data	empty;
	t_data	wall;
	t_data	closed;
	t_data	fin;
}				t_images;

typedef struct s_gl
{
	t_vars		win;
	t_images	images;
	t_map		map;
	int			done;
}				t_gl;

int		read_and_check_map(t_map *map, char *map_name);
int		going(t_gl *gl, int keycode);
int		bug(char *s);
int		fin(t_gl *gl);

size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
void	fin_walls(t_gl *gl);
void	draw_exits(t_gl *gl);
void	ft_putnbr(int n, int fd);
void	destroy(t_map *map);
void	destroy_global(t_gl *gl);
void	game(t_vars *win, t_data *img, t_map *map, t_images *images);
void	exit_serv(int line, int symb, t_gl *gl);
#endif