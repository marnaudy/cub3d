/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:41:49 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/08 16:02:11 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <X11/X.h>
#include "mlx.h"

void	print_parse_info(t_map *map)
{
	printf("Colours : Ceiling = %x, floor = %x\n", map->ceiling, map->floor);
	printf("Filenames : North = %s, South = %s, East = %s, West = %s\n", map->north_text.name, map->south_text.name, map->east_text.name, map->west_text.name);
	printf("Map size : width = %i, height = %i\n", map->n_col, map->n_lin);
	printf("Map : %s\n", map->map);
}

int main(int argc, char **argv)
{
	t_map		map;
	t_player	player;
	t_mlx		mlx;
	t_bundle	bundle;

	init_map(&map);
	init_player(&player);

	int ret = parse(argc, argv, &map, &player);
	print_parse_info(&map);
	if (ret)
		exit(1);
	bundle.mlx = &mlx;
	bundle.map = &map;
	bundle.player = &player;
	if (start_mlx(&mlx) || load_all_textures(&mlx, &map))
	{
		free_map(&map);
		close_mlx(&mlx, &map);
		return (1);
	}
	new_frame(&mlx, &player, &map);
	mlx_hook(mlx.win_ptr, KeyPress, KeyPressMask, deal_key_press, &bundle);
	mlx_hook(mlx.win_ptr, KeyRelease, KeyReleaseMask, deal_key_release, &bundle);
	mlx_hook(mlx.win_ptr, DestroyNotify, NoEventMask, exit_cube, &bundle); 
	mlx_loop_hook(mlx.mlx_ptr, update, &bundle);
	mlx_loop(mlx.mlx_ptr);
	close_mlx(&mlx, &map);
}
