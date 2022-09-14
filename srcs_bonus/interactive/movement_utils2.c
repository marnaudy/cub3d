/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:47:44 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/14 10:49:32 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	turn_left(t_player *player)
{
	double	temp_x;

	temp_x = player->dir_x;
	player->dir_x = player->dir_x * COS_A + player->dir_y * SIN_A;
	player->dir_y = player->dir_y * COS_A - temp_x * SIN_A;
	player->plane_x = -player->dir_y * SQRT3_6;
	player->plane_y = player->dir_x * SQRT3_6;
}

void	small_turns_left(t_player *player, int n)
{
	double	temp_x;
	int		i;

	i = 0;
	while (i < n)
	{
		temp_x = player->dir_x;
		player->dir_x = player->dir_x * COS_B + player->dir_y * SIN_B;
		player->dir_y = player->dir_y * COS_B - temp_x * SIN_B;
		player->plane_x = -player->dir_y * SQRT3_6;
		player->plane_y = player->dir_x * SQRT3_6;
		i++;
	}
}

void	small_turns_right(t_player *player, int n)
{
	double	temp_x;
	int		i;

	i = 0;
	while (i < n)
	{
		temp_x = player->dir_x;
		player->dir_x = player->dir_x * COS_B - player->dir_y * SIN_B;
		player->dir_y = player->dir_y * COS_B + temp_x * SIN_B;
		player->plane_x = -player->dir_y * SQRT3_6;
		player->plane_y = player->dir_x * SQRT3_6;
		i++;
	}
}
