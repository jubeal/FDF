/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:12:33 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/24 13:44:10 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		init_t_map(t_map **map)
{
	if (!(*map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	(*map)->x_max = 0;
	(*map)->y_max = -1;
	(*map)->z_max = 0;
	(*map)->z_min = -1;
	(*map)->ptr = NULL;
	(*map)->win = NULL;
	(*map)->first = NULL;
	(*map)->last = NULL;
	(*map)->zoom = 0;
	if (!((*map)->curent = init_t_color()))
		return (0);
	(*map)->affichage = 0;
	(*map)->img = NULL;
	(*map)->data = NULL;
	(*map)->bpp = 0;
	(*map)->size_line = 0;
	(*map)->endian = 0;
	(*map)->merge_x = WIN_X / 2.7;
	(*map)->merge_y = WIN_Y / 10;
	(*map)->merge_para_x = WIN_X / 3.5;
	(*map)->merge_para_y = WIN_Y / 5;
	return (1);
}

void	init_points(t_point **points, t_map *map)
{
	t_point	*tmp;

	tmp = *points;
	while (tmp->next)
		tmp = tmp->next;
	map->last = tmp;
	map->first = *points;
	map->zoom = (WIN_X * 0.3) / map->x_max + 1;
	map->zoomz = 0;
}
