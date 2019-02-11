/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:34:32 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/04 13:31:59 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		init_t_point(t_point **maillon, int x, int y, char *z)
{
	int		i;
	int		verif;

	i = -1;
	verif = 0;
	(*maillon)->x = x;
	(*maillon)->y = y;
	while (z[++i])
	{
		if (z[i] != '-')
		{
			if (!ft_isdigit(z[i]))
				return (0);
		}
		else
		{
			if ((++verif) > 1)
				return (0);
		}
	}
	(*maillon)->z = ft_atoi(z);
	(*maillon)->truex = 0;
	(*maillon)->truey = 0;
	(*maillon)->next = NULL;
	return (1);
}

int		create_t_point(t_point **maillon, int x, int y, char *z)
{
	t_point	*tmp;

	tmp = *maillon;
	if (!(*maillon))
	{
		if (!(*maillon = (t_point *)malloc(sizeof(t_point))))
			return (0);
		tmp = *maillon;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_point *)malloc(sizeof(t_point))))
			return (0);
		tmp->next->prev = tmp;
		tmp = tmp->next;
	}
	return (init_t_point(&tmp, x, y, z));
}

int		file_reader(int fd, t_point **points, t_map *map)
{
	char	*line;
	char	**line_split;
	int		x;

	while (get_next_line(fd, &line))
	{
		map->y_max++;
		line_split = ft_strsplit(line, ' ');
		x = -1;
		while (line_split[++x])
			if (!create_t_point(points, x, map->y_max, line_split[x]))
				return (0);
		if (map->x_max == 0)
			map->x_max = x - 1;
		if (x - 1 != map->x_max)
			return (0);
	}
	if (map->x_max == 0)
		return (0);
	init_points(points, map);
	return (1);
}
