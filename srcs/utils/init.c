/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:23:48 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/07 17:03:09 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->dir_len = 1.0;
	player->moving_forward = 0;
	player->moving_back = 0;
	player->turning_left = 0;
	player->turning_right = 0;
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->north_text_name = NULL;
	map->south_text_name = NULL;
	map->east_text_name = NULL;
	map->west_text_name = NULL;
	map->ceiling = 0;
	map->floor = 0;
	map->north_colour = 0x00FF0000;
	map->south_colour = 0x0000FF00;
	map->east_colour = 0x000000FF;
	map->west_colour = 0x0000FFFF;
}
