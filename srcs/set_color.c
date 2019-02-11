/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 13:10:02 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/04 13:28:10 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color		*init_t_color(void)
{
	t_color	*ret;
	t_color *tmp;

	if (!(ret = (t_color *)malloc(sizeof(t_color))))
		return (NULL);
	ret->color_2 = 0x0000CC;
	ret->color_1 = 0x3399FF;
	ret->color = 0x00CC00;
	ret->color1 = 0x994C00;
	ret->color2 = 0xFFFFFF;
	if (!(ret->next = (t_color *)malloc(sizeof(t_color))))
		return (NULL);
	tmp = ret->next;
	tmp->color_2 = 0xFFFFFF;
	tmp->color_1 = 0x99FF33;
	tmp->color = 0xFFFF00;
	tmp->color1 = 0xFF9A00;
	tmp->color2 = 0xFF00A2;
	tmp->next = ret;
	return (ret);
}

void		change_color(t_map *map)
{
	map->curent = map->curent->next;
	if (map->affichage)
		draw_paral(map);
	else
		rotation_points(map);
}

int			color_set(t_point *to, t_point *from, t_map *map)
{
	if (from->z < (map->z_min / 3) && to->z < (map->z_min / 3)
			&& map->zoomz > 0)
		return (map->curent->color_2);
	if (from->z < 0 && to->z < 0 && map->zoomz > 0)
		return (map->curent->color_1);
	if (from->z > ((map->z_max / 3) * 2) && to->z > ((map->z_max / 3) * 2)
			&& map->zoomz > 0)
		return (map->curent->color2);
	if (from->z > (map->z_max / 3) && to->z > (map->z_max / 3)
			&& map->zoomz > 0)
		return (map->curent->color1);
	return (map->curent->color);
}
