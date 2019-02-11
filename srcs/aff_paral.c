/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_paral.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 12:29:48 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/24 13:42:34 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_paral(t_map *map)
{
	t_point *tmp;
	int		x;
	int		y;

	tmp = map->first;
	while (tmp)
	{
		x = tmp->x * map->zoom;
		y = tmp->y * map->zoom;
		tmp->truex = (int)(x - tmp->z * map->zoomz) + map->merge_para_x;
		tmp->truey = (int)(y - tmp->z * map->zoomz) + map->merge_para_y;
		tmp = tmp->next;
	}
	map->affichage = 1;
	draw_wires(map);
}

void	change_aff(t_map *map)
{
	ft_bzero(map->data, WIN_X * WIN_Y * 4);
	if (map->affichage == 0)
		draw_paral(map);
	else
		rotation_points(map);
}
