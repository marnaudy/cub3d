/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:41:49 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/06 12:01:58 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>
#include <math.h>

int main(void)
{
	t_map		map;
	map.n_col = 5;
	map.n_lin = 5;
	map.map = "1111110001100011000111111";
	// map.map =    "1100000000000000000001000";
	map.ceiling = 0;
	map.floor = 0x00FFFFFF;
	map.north = 0x00FF0000;
	map.south = 0x0000FF00;
	map.east = 0x000000FF;
	map.west = 0x0000FFFF;

	t_player	player;
	player.x = 2.5;
	player.y = 2.5;
	player.dir_x = 0.7;
	player.dir_y = 0.7;
	player.dir_len = sqrt(pow(player.dir_x, 2.0) + pow(player.dir_y, 2.0));
	player.plane_x = -0.4;
	player.plane_y = 0.4;

	t_mlx	mlx;
	if (start_mlx(&mlx))
		return (1);
	new_frame(&mlx, &player, &map);
	sleep(4);
	close_mlx(&mlx);
}
