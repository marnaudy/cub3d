/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:51:39 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/14 10:14:20 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_ray_data(t_player *player, int ray_nb, t_ray_calc *data)
{
	data->camera_x = (ray_nb - (double) WIN_WIDTH / 2) / WIN_WIDTH * 2;
	data->ray_dir_x = player->dir_x + player->plane_x * data->camera_x;
	data->ray_dir_y = player->dir_y + player->plane_y * data->camera_x;
	data->map_x = (int) player->x;
	data->map_y = (int) player->y;
	data->delta_x = fabs(1.0 / data->ray_dir_x);
	data->delta_y = fabs(1.0 / data->ray_dir_y);
}

void	init_step_delta(t_player *player, t_ray_calc *data)
{
	if (data->ray_dir_x < 0 && player->x > 0.0)
	{
		data->step_x = -1;
		data->dist_x = (player->x - data->map_x) * data->delta_x;
	}
	else
	{
		data->step_x = 1;
		data->dist_x = (data->map_x + 1.0 - player->x) * data->delta_x;
	}
	if ((data->ray_dir_y < 0 && player->y > 0.0)
		|| (data->ray_dir_y > 0 && player->y < 0.0))
	{
		data->step_y = -1;
		data->dist_y = (player->y - data->map_y) * data->delta_y;
	}
	else
	{
		data->step_y = 1;
		data->dist_y = (data->map_y + 1.0 - player->y) * data->delta_y;
	}
}

void	cast_dda(t_map *map, t_ray_calc *data, t_line *line)
{
	while (1)
	{
		if (data->dist_x < data->dist_y)
		{
			data->dist_x += data->delta_x;
			data->map_x += data->step_x;
			line->type = west;
		}
		else
		{
			data->dist_y += data->delta_y;
			data->map_y += data->step_y;
			line->type = north;
		}
		if (data->map_x < 0 || data->map_y < 0 || data->map_x >= map->n_col
			|| data->map_y >= map->n_lin)
		{
			line->distance = INFINITY;
			line->wall_x = 0.1;
			break ;
		}
		if (map->map[data->map_y * map->n_col + data->map_x] == '1')
			break ;
	}
}

void	calc_line_x(t_player *player, t_ray_calc *data, t_line *line)
{
	line->wall_x = player->y + data->ray_dir_y
		* (data->dist_x - data->delta_x);
	line->wall_x -= (int) line->wall_x;
	if (data->ray_dir_x < 0)
	{
		line->wall_x = 1 - line->wall_x;
		line->type = east;
	}
	line->distance = data->dist_x - data->delta_x;
}

void	calc_line_y(t_player *player, t_ray_calc *data, t_line *line)
{
	line->wall_x = player->x + data->ray_dir_x
		* (data->dist_y - data->delta_y);
	line->wall_x -= (int) line->wall_x;
	if (data->ray_dir_y < 0)
		line->type = south;
	else
		line->wall_x = 1 - line->wall_x;
	line->distance = data->dist_y - data->delta_y;
}
