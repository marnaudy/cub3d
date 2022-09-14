/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:36:19 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/14 10:16:21 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_in_wall(t_ray_calc *data, t_line *line)
{
	if (data->dist_x < data->dist_y)
	{
		data->dist_x += data->delta_x;
		line->type = west;
	}
	else
	{
		data->dist_y += data->delta_y;
		line->type = north;
	}
}

void	cast_ray(t_player *player, t_map *map, int ray_nb, t_line *line)
{
	t_ray_calc	data;

	init_ray_data(player, ray_nb, &data);
	init_step_delta(player, &data);
	if (data.map_x < 0 || data.map_y < 0 || data.map_x >= map->n_col
		|| data.map_y >= map->n_lin
		|| map->map[data.map_y * map->n_col + data.map_x] == '1')
		cast_in_wall(&data, line);
	else
		cast_dda(map, &data, line);
	if (data.map_x < 0 || data.map_y < 0 || data.map_x > map->n_col
		|| data.map_y >= map->n_lin)
		return ;
	if (line->type == west)
		calc_line_x(player, &data, line);
	else
		calc_line_y(player, &data, line);
}

int	new_frame(t_mlx *mlx, t_player *player, t_map *map)
{
	t_img	old_img;
	int		x;
	t_line	line;

	old_img = mlx->img;
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img.img_ptr)
		return (-1);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr,
			&mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.addr)
		return (-1);
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_ray(player, map, x, &line);
		draw_line(mlx, map, &line, x);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, old_img.img_ptr);
	return (0);
}
