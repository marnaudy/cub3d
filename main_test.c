/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:41:49 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/05 16:29:10 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

int main(void)
{
	t_map		map;
	map.n_col = 5;
	map.n_lin = 5;
	map.map = "1111110001101011000111111";
	map.ceiling.r = 0;
	map.ceiling.g = 0;
	map.ceiling.b = 0;
	map.floor.r = 255;
	map.floor.g = 255;
	map.floor.b = 255;
	map.north.r = 0;
	map.north.g = 0;
	map.north.b = 255;
	map.south.r = 255;
	map.south.g = 0;
	map.south.b = 0;
	map.east.r = 0;
	map.east.g = 255;
	map.east.b = 255;
	map.west.r = 0;
	map.west.g = 255;
	map.west.b = 0;

	t_player	player;
	player.x = 1.5;
	player.y = 1.5;
	player.dir_x = 1.0;
	player.dir_y = 0.0;
	player.cam_dir_x = 0.0;
	player.cam_dir_y = -1.0;

	t_mlx	mlx;
	if (start_mlx(&mlx))
		return (1);
	sleep(2);
	close_mlx(&mlx);
}
