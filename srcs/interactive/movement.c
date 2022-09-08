/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:23:13 by cboudrin          #+#    #+#             */
/*   Updated: 2022/09/08 12:48:53 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <X11/keysym.h>

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

void	turn_left(t_player *player)
{
	double	temp_x;

	temp_x = player->dir_x;
	player->dir_x = player->dir_x * COS_A + player->dir_y * SIN_A;
	player->dir_y = player->dir_y * COS_A - temp_x * SIN_A;
	player->plane_x = -player->dir_y * SQRT3_6;
	player->plane_y = player->dir_x * SQRT3_6;
}

int	deal_key_press(int keycode, t_bundle *bundle)
{
	if (keycode != XK_Escape && keycode != XK_w
		&& keycode != XK_s && keycode != XK_a && keycode != XK_d
		&& keycode != XK_Up && keycode != XK_Down
		&& keycode != XK_Left && keycode != XK_Right)
		return (0);
	if (keycode == XK_Escape)
	{
		printf("you have closed the window.\n");
		exit_cube(bundle);
	}
	if (keycode == XK_w || keycode == XK_Up)
		bundle->player->moving_forward = 1;
	if (keycode == XK_s || keycode == XK_Down)
		bundle->player->moving_back = 1;
	if (keycode == XK_a)
		bundle->player->moving_left = 1;
	if (keycode == XK_d)
		bundle->player->moving_right = 1;
	if (keycode == XK_Left)
		bundle->player->turning_left = 1;
	if (keycode == XK_Right)
		bundle->player->turning_right = 1;
	return (0);
}

int	deal_key_release(int keycode, t_bundle *bundle)
{
	if (keycode != XK_w && keycode != XK_s && keycode != XK_a
		&& keycode != XK_d && keycode != XK_Up && keycode != XK_Down
		&& keycode != XK_Left && keycode != XK_Right)
		return (0);
	if (keycode == XK_w || keycode == XK_Up)
		bundle->player->moving_forward = 0;
	if (keycode == XK_s || keycode == XK_Down)
		bundle->player->moving_back = 0;
	if (keycode == XK_a)
		bundle->player->moving_left = 0;
	if (keycode == XK_d)
		bundle->player->moving_right = 0;
	if (keycode == XK_Left)
		bundle->player->turning_left = 0;
	if (keycode == XK_Right)
		bundle->player->turning_right = 0;
	return (0);
}

void	update_player(t_player *player)
{
	if (player->moving_forward)
		move_up(player);
	if (player->moving_back)
		move_down(player);
	if (player->moving_left)
		move_left(player);
	if (player->moving_right)
		move_right(player);
	if (player->turning_right)
		turn_right(player);
	if (player->turning_left)
		turn_left(player);
}

int	update(t_bundle *bundle)
{
	update_player(bundle->player);
	new_frame(bundle->mlx, bundle->player, bundle->map);
	return (0);
}
