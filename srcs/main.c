/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jubeal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:56:57 by jubeal            #+#    #+#             */
/*   Updated: 2019/01/04 12:21:12 by jubeal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	deal_key(int key, t_map *map)
{
	if (key == 53)
		exit(0);
	if (key == 123 || key == 124 || key == 125 || key == 126)
		translate_points(map, key);
	if (key == 27 || key == 24 || key == 78 || key == 69)
		zoom_points(map, key);
	if (key == 43 || key == 47)
		heigth_difference(map, key);
	if (key == 2)
		change_aff(map);
	if (key == 8)
		change_color(map);
	return (0);
}

int			error(int n)
{
	if (n == 1)
		ft_putstr("usage: ./fdf map_file\n");
	if (n == 2)
		ft_putstr("error\n");
	return (1);
}

void		aff_comands(t_map *map)
{
	mlx_string_put(map->ptr, map->win, 10,
			10, 0xFFFFFF, "up, down, left, rigth, : move map");
	mlx_string_put(map->ptr, map->win, 10,
			30, 0xFFFFFF, "> < : heigth difference");
	mlx_string_put(map->ptr, map->win, 10,
			50, 0xFFFFFF, "+ - : zoom");
	mlx_string_put(map->ptr, map->win, 10,
			70, 0xFFFFFF, "d : change display");
	mlx_string_put(map->ptr, map->win, 10,
			90, 0xFFFFFF, "c : change color");
}

static void	fdf(t_map *map)
{
	void	*ptr;
	void	*win;

	if (!(ptr = mlx_init()))
	{
		ft_putstr("manque de place pour mlx_init\n");
		exit(0);
	}
	win = mlx_new_window(ptr, WIN_X, WIN_Y, "FdF");
	map->ptr = ptr;
	map->win = win;
	if (!(map->img = mlx_new_image(ptr, WIN_X, WIN_Y)))
	{
		ft_putstr("manque de place pour new_image\n");
		exit(0);
	}
	if (!(map->data = mlx_get_data_addr(map->img, &map->bpp,
					&map->size_line, &map->endian)))
	{
		ft_putstr("manque de place pour data_addr\n");
		exit(0);
	}
	rotation_points(map);
	mlx_hook(win, 2, (1L << 1), deal_key, map);
	mlx_loop(ptr);
}

int			main(int ac, char **av)
{
	int			fd;
	t_map		*map;
	t_point		*first;

	fd = -1;
	first = NULL;
	if (ac != 2)
		return (error(1));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (error(2));
	if (!init_t_map(&map))
		return (error(2));
	if (!file_reader(fd, &first, map))
		return (error(2));
	fdf(map);
	return (0);
}
