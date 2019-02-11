/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wires.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:54:58 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/03 14:20:31 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	pixel_put_img(int x, int y, t_map *map, int color)
{
	int		pixel;

	pixel = x * 4 + y * map->size_line;
	if (pixel < 0 || pixel > WIN_X * WIN_Y * 4)
		return ;
	map->data[pixel] = color & 0xFF;
	map->data[pixel + 1] = color >> 8 & 0xFF;
	map->data[pixel + 2] = color >> 16 & 0xFF;
}

static void	bresenham_draw2(t_point *from, t_point *to, t_map *map,
		t_brese_para *param)
{
	int		cumul;
	int		x;
	int		y;

	x = from->truex;
	y = from->truey;
	cumul = param->dy;
	while (y != to->truey)
	{
		y += param->yinc;
		cumul -= param->dx * 2;
		if (cumul <= 0)
		{
			cumul += param->dy * 2;
			x += param->xinc;
		}
		if (x >= 0 && y >= 0 && x < WIN_X && y < WIN_Y)
			pixel_put_img(x, y, map, color_set(to, from, map));
	}
}

static void	bresenham_draw(t_point *from, t_point *to, t_map *map,
		t_brese_para *param)
{
	int		cumul;
	int		x;
	int		y;

	x = from->truex;
	y = from->truey;
	if (x >= 0 && y >= 0 && x < WIN_X && y < WIN_Y)
		pixel_put_img(x, y, map, color_set(to, from, map));
	if (param->dx > param->dy)
	{
		cumul = param->dx;
		while (x != to->truex)
		{
			x += param->xinc;
			cumul -= param->dy * 2;
			if (cumul <= 0 && ((y += param->yinc) || !(y)))
				cumul += param->dx * 2;
			if (x >= 0 && y >= 0 && (x < WIN_X && y < WIN_Y))
				pixel_put_img(x, y, map, color_set(to, from, map));
		}
	}
	else
		bresenham_draw2(from, to, map, param);
}

void		bresenham(t_point *from, t_point *to, t_map *map)
{
	t_brese_para	*param;
	int				xinc;
	int				yinc;
	int				dx;
	int				dy;

	dx = to->truex - from->truex;
	dy = to->truey - from->truey;
	xinc = (dx > 0) ? 1 : -1;
	yinc = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	if (!(param = (t_brese_para *)malloc(sizeof(t_brese_para))))
	{
		ft_putstr("manque de place memoire\n");
		exit(0);
	}
	param->xinc = xinc;
	param->yinc = yinc;
	param->dx = dx;
	param->dy = dy;
	bresenham_draw(from, to, map, param);
}

void		draw_wires(t_map *map)
{
	t_point	*tmp;
	t_point	*tmp2;
	int		i;

	tmp = map->first;
	tmp2 = tmp;
	i = -1;
	while (++i < map->x_max + 1)
		tmp2 = tmp2->next;
	while (tmp->next)
	{
		if (tmp->next->x != 0)
			bresenham(tmp, tmp->next, map);
		if (tmp2)
			bresenham(tmp, tmp2, map);
		if (tmp2)
			tmp2 = tmp2->next;
		tmp = tmp->next;
	}
	mlx_put_image_to_window(map->ptr, map->win, map->img, 0, 0);
	aff_comands(map);
}
