/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:32:04 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/14 10:53:26 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#define SPEED_F_B 0.1
#define SPEED_L_R 0.05

void	move_up(t_player *player, t_map *map)
{
	t_line	line;

	cast_ray(player, map, WIN_WIDTH / 2, &line);
	if (line.distance <= SPEED_F_B + 0.1)
		return ;
	player->x = player->x + (player->dir_x) * SPEED_F_B;
	player->y = player->y + (player->dir_y) * SPEED_F_B;
}

void	move_down(t_player *player, t_map *map)
{
	t_line	line;

	player->dir_x = -player->dir_x;
	player->dir_y = -player->dir_y;
	cast_ray(player, map, WIN_WIDTH / 2, &line);
	player->dir_x = -player->dir_x;
	player->dir_y = -player->dir_y;
	if (line.distance <= SPEED_F_B + 0.1)
		return ;
	player->x = player->x - (player->dir_x) * SPEED_F_B;
	player->y = player->y - (player->dir_y) * SPEED_F_B;
}

void	move_right(t_player *player, t_map *map)
{
	t_line	line;
	double	save;

	save = player->dir_x;
	player->dir_x = -player->dir_y;
	player->dir_y = save;
	cast_ray(player, map, WIN_WIDTH / 2, &line);
	save = player->dir_x;
	player->dir_x = player->dir_y;
	player->dir_y = -save;
	if (line.distance <= SPEED_L_R + 0.1)
		return ;
	player->x = player->x - (player->dir_y) * SPEED_L_R;
	player->y = player->y + (player->dir_x) * SPEED_L_R;
}

void	move_left(t_player *player, t_map *map)
{
	t_line	line;
	double	save;

	save = player->dir_x;
	player->dir_x = player->dir_y;
	player->dir_y = -save;
	cast_ray(player, map, WIN_WIDTH / 2, &line);
	save = player->dir_x;
	player->dir_x = -player->dir_y;
	player->dir_y = save;
	if (line.distance <= SPEED_L_R + 0.1)
		return ;
	player->x = player->x + (player->dir_y) * SPEED_L_R;
	player->y = player->y - (player->dir_x) * SPEED_L_R;
}

void	turn_right(t_player *player)
{
	double	temp_x;

	temp_x = player->dir_x;
	player->dir_x = player->dir_x * COS_A - player->dir_y * SIN_A;
	player->dir_y = player->dir_y * COS_A + temp_x * SIN_A;
	player->plane_x = -player->dir_y * SQRT3_6;
	player->plane_y = player->dir_x * SQRT3_6;
}
