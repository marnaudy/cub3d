/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:41:49 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/07 14:46:41 by marnaudy         ###   ########.fr       */
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
	printf("Filenames : North = %s, South = %s, East = %s, West = %s\n", map->north_text_name, map->south_text_name, map->east_text_name, map->west_text_name);
}

int main(int argc, char **argv)
{
	t_map		map;
	init_map(&map);
	map.n_col = 7;
	map.n_lin = 7;
	// map.map = "1111110001100011000111111";
	// map.map = "1111111
	// 		  	  1000001
	// 		   	  1011001
	// 		      1011001
	// 		      1000001
	// 		      1000001
	// 		      1111111";
	// map.map = "1111111100000110000011000001100000110000011111111";
	map.map = "1111111100000110110011011001100000110000011111111";
	// map.map =    "1111110001100011000111111";

	t_player	player;
	init_player(&player);
	player.x = 1.5;
	player.y = 1.5;
	player.dir_x = 0.0;
	player.dir_y = 1.0;
	player.dir_len = sqrt(pow(player.dir_x, 2.0) + pow(player.dir_y, 2.0));
	player.plane_x = player.dir_y * sqrt(3) / 6;
	player.plane_y = -player.dir_x * sqrt(3) / 6;

	
	t_mlx	mlx;
	t_bundle	bundle;

	int ret = parse(argc, argv, &map, &player);
	print_parse_info(&map);
	if (ret)
		exit(1);
	bundle.mlx = &mlx;
	bundle.map = &map;
	bundle.player = &player;
	if (start_mlx(&mlx))
		return (1);
	
	new_frame(&mlx, &player, &map);
	mlx_hook(mlx.win_ptr, KeyPress, KeyPressMask, deal_key_press, &bundle);
	mlx_hook(mlx.win_ptr, KeyRelease, KeyReleaseMask, deal_key_release, &bundle);
	mlx_hook(mlx.win_ptr, DestroyNotify, NoEventMask, exit_cube, &bundle); 
	mlx_loop_hook(mlx.mlx_ptr, update, &bundle);
	mlx_loop(mlx.mlx_ptr);
	close_mlx(&mlx);
}
