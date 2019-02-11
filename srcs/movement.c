/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:53:44 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/24 13:54:04 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		rotation_points(t_map *map)
{
	t_point	*tmp;
	float	phi;
	int		x;
	int		y;
	int		z;

	tmp = map->first;
	phi = 0.55;
	while (tmp)
	{
		x = (tmp->x * map->zoom * cos(phi)) + (tmp->y * map->zoom
				* -sin(phi));
		y = (tmp->x * map->zoom * sin(phi)) + (tmp->y * map->zoom * cos(phi));
		z = tmp->z * 1;
		tmp->truex = x + map->merge_x;
		tmp->z = z;
		tmp->truey = (y - z * map->zoomz) + map->merge_y;
		if (map->z_max < tmp->z)
			map->z_max = tmp->z;
		if (map->z_min > tmp->z)
			map->z_min = tmp->z;
		tmp = tmp->next;
	}
	map->affichage = 0;
	draw_wires(map);
}

void		translate_points(t_map *map, int direction)
{
	int		directionx;
	int		directiony;
	t_point	*tmp;

	tmp = map->first;
	directionx = 0;
	directiony = 0;
	ft_bzero(map->data, WIN_X * WIN_Y * 4);
	if (direction == 125)
		directiony -= 5;
	if (direction == 126)
		directiony += 5;
	if (direction == 123)
		directionx += 5;
	if (direction == 124)
		directionx -= 5;
	map->merge_x += directionx;
	map->merge_y += directiony;
	map->merge_para_x += directionx;
	map->merge_para_y += directiony;
	if (map->affichage)
		draw_paral(map);
	else
		rotation_points(map);
}

void		zoom_points(t_map *map, int direction)
{
	ft_bzero(map->data, WIN_X * WIN_Y * 4);
	if (direction == 24 || direction == 69)
	{
		map->zoom += 1;
		if (map->affichage)
			draw_paral(map);
		else
			rotation_points(map);
		return ;
	}
	if (map->zoom - 1 > 0)
		map->zoom -= 1;
	if (map->affichage)
		draw_paral(map);
	else
		rotation_points(map);
}

void		heigth_difference(t_map *map, int direction)
{
	ft_bzero(map->data, WIN_X * WIN_Y * 4);
	if (direction == 43)
		map->zoomz -= 0.2;
	else
		map->zoomz += 0.2;
	if (map->affichage)
		draw_paral(map);
	else
		rotation_points(map);
}
