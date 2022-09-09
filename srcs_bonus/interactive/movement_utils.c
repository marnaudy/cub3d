/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:32:04 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/09 12:39:21 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#define SPEED_F_B 0.1
#define SPEED_L_R 0.05

void	move_up(t_player *player)
{
	player->x = player->x + (player->dir_x) * SPEED_F_B;
	player->y = player->y + (player->dir_y) * SPEED_F_B;
}

void	move_down(t_player *player)
{
	player->x = player->x - (player->dir_x) * SPEED_F_B;
	player->y = player->y - (player->dir_y) * SPEED_F_B;
}

void	move_right(t_player *player)
{
	player->x = player->x - (player->dir_y) * SPEED_L_R;
	player->y = player->y + (player->dir_x) * SPEED_L_R;
}

void	move_left(t_player *player)
{
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
