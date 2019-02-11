/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:34:43 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/24 13:41:16 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <mlx.h>
# include <math.h>
# include "get_next_line.h"
# define WIN_X 2560
# define WIN_Y 1315

typedef struct		s_point
{
	int				z;
	int				x;
	int				y;
	int				truex;
	int				truey;
	struct s_point	*next;
	struct s_point	*prev;
}					t_point;

typedef struct		s_color
{
	int				color_2;
	int				color_1;
	int				color;
	int				color1;
	int				color2;
	struct s_color	*next;
}					t_color;

typedef struct		s_map
{
	int				x_max;
	int				y_max;
	int				z_max;
	int				z_min;
	int				zoom;
	float			zoomz;
	void			*ptr;
	void			*win;
	t_point			*first;
	t_point			*last;
	t_color			*curent;
	int				affichage;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	int				merge_x;
	int				merge_y;
	int				merge_para_x;
	int				merge_para_y;
}					t_map;

typedef struct		s_brese_para
{
	int				xinc;
	int				yinc;
	int				dx;
	int				dy;
}					t_brese_para;

int					file_reader(int fd, t_point **points, t_map *map);
int					error(int n);
void				draw_wires(t_map *map);
void				rotation_points(t_map *map);
void				bresenham(t_point *from, t_point *to, t_map *map);
void				translate_points(t_map *map, int direction);
void				zoom_points(t_map *map, int direction);
void				heigth_difference(t_map *map, int direction);
int					init_t_map(t_map **map);
t_color				*init_t_color();
void				init_points(t_point **points, t_map *map);
void				draw_paral(t_map *map);
void				change_aff(t_map *map);
void				change_color(t_map *map);
int					color_set(t_point *to, t_point *from, t_map *map);
void				aff_comands(t_map *map);
#endif
