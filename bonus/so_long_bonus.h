/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:28:36 by mbesan            #+#    #+#             */
/*   Updated: 2022/01/27 15:48:08 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef DENSITY
#  define DENSITY 12
# endif

# ifndef PATROLS
#  define PATROLS 7
# endif

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
	char	*m_name;
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
	int		d_x;
	int		d_y;
	int		pt_n;
	char	**body;
	int		ptr[2][PATROLS];
}				t_map;

typedef struct s_images
{
	t_data	plr;
	t_data	collectibles;
	t_data	exit;
	t_data	plr_right;
	t_data	plr_dead;
	t_data	dead_peer;
	t_data	hp;
	t_data	empty;
	t_data	wall;
	t_data	closed;
	t_data	fin;
	t_data	patr;
	t_data	step_r;
	t_data	step_l;
}				t_images;

typedef struct s_imac
{
	t_data	body[10];
	t_data	score;
	t_data	text;
}				t_imac;

typedef struct s_gl
{
	t_vars		win;
	t_images	images;
	t_map		map;
	t_data		img;
	t_imac		imac;
	int			done;
}				t_gl;

int		going(t_gl *gl, int keycode, int orientation);
int		read_and_check_map(t_map *map, char *map_name);
int		check_if_patrol(t_gl *gl, int x, int y, int ptrls);
int		key_hook(int keycode, t_gl *gl);
int		death(t_gl *gl, int x, int y);
int		sprites(t_gl *gl);
int		bug(char *s);
int		fin(t_gl *gl);

size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*ft_itoa(int n);

void	step(t_gl *gl);
void	destroy(t_map *map);
void	destroy_global(t_gl *gl, int flag);
void	pers(t_gl *pers);
void	fin_walls(t_gl *gl);
void	imacs(t_gl *gl, int a);
void	draw_exits(t_gl *gl);
void	ft_putnbr(int n, int fd);
void	draw_exit_again(t_gl *gl);
void	exit_serv(int line, int symb, t_gl *gl);
void	death_walls(t_gl *gl, t_data lost);
void	patrols(t_vars *win, t_map *map, t_images *images, int volume);
void	game(t_vars *win, t_data *img, t_map *map, t_images *images);
void	init_global_struct_and_hooks(t_vars *win, t_map *map, t_images *images,
			t_data *img);
t_data	putim(t_vars *win, t_data *img, char *path);

#endif
