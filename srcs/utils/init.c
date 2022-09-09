/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:23:48 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/09 12:44:04 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->moving_forward = 0;
	player->moving_back = 0;
	player->moving_left = 0;
	player->moving_right = 0;
	player->turning_left = 0;
	player->turning_right = 0;
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->north_text.name = NULL;
	map->south_text.name = NULL;
	map->east_text.name = NULL;
	map->west_text.name = NULL;
	map->north_text.img.img_ptr = NULL;
	map->south_text.img.img_ptr = NULL;
	map->east_text.img.img_ptr = NULL;
	map->west_text.img.img_ptr = NULL;
	map->ceiling = 0;
	map->floor = 0;
}
