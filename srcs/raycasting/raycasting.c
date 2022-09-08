/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:36:19 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/08 16:37:46 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WALL_RATIO 1.8

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
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->dist_x = (player->x - data->map_x) * data->delta_x;
	}
	else
	{
		data->step_x = 1;
		data->dist_x = (data->map_x + 1.0 - player->x) * data->delta_x;
	}
	if (data->ray_dir_y < 0)
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
		if (data->map_x < 0 || data->map_y < 0 || data->map_x >= map->n_lin
			|| data->map_y >= map->n_lin)
		{
			line->distance = INFINITY;
			line->wall_x = 0.0;
			break ;
		}
		if (map->map[data->map_y * map->n_col + data->map_x] == '1')
			break ;
	}
}

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

void	cast_ray(t_player *player, t_map *map, int ray_nb, t_line *line)
{
	t_ray_calc	data;

	init_ray_data(player, ray_nb, &data);
	init_step_delta(player, &data);
	if (map->map[data.map_y * map->n_col + data.map_x] == '1')
		cast_in_wall(&data, line);
	else
		cast_dda(map, &data, line);
	if (data.map_x < 0 || data.map_y < 0 || data.map_x > map->n_lin
		|| data.map_y >= map->n_lin)
		return ;
	if (line->type == west)
		calc_line_x(player, &data, line);
	else
		calc_line_y(player, &data, line);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int colour)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

t_texture	*get_wall_texture(t_map *map, enum e_dir dir)
{
	if (dir == north)
		return (&map->north_text);
	if (dir == south)
		return (&map->south_text);
	if (dir == east)
		return (&map->east_text);
	return (&map->west_text);
}

void	draw_floor_and_ceiling(t_mlx *mlx, t_map *map,
			t_line *line, int ray_nb)
{
	int	line_height;
	int	y;

	line_height = (int)(WIN_HEIGHT / line->distance) * WALL_RATIO;
	if (line->distance < 0.000001)
		line_height = WIN_HEIGHT;
	y = 0;
	while (y < WIN_HEIGHT / 2 - line_height / 2)
	{
		my_mlx_pixel_put(&mlx->img, ray_nb, y, map->ceiling);
		y++;
	}
	y = WIN_HEIGHT;
	while (y >= line_height / 2 + WIN_HEIGHT / 2)
	{
		my_mlx_pixel_put(&mlx->img, ray_nb, y, map->floor);
		y--;
	}
}

void	draw_line(t_mlx *mlx, t_map *map, t_line *line, int ray_nb)
{
	int				wall_height;
	int				y;
	unsigned int	tex_colour;
	t_texture		*texture;
	char			*src;

	draw_floor_and_ceiling(mlx, map, line, ray_nb);
	wall_height = (int)(WIN_HEIGHT / line->distance) * WALL_RATIO;
	if (line->distance < 0.000001)
		wall_height = WIN_HEIGHT;
	y = WIN_HEIGHT / 2 - wall_height / 2;
	texture = get_wall_texture(map, line->type);
	if (y < 0)
		y = 0;
	while (y < wall_height / 2 + WIN_HEIGHT / 2 && y < WIN_HEIGHT)
	{
		src = texture->img.addr + ((int)(texture->height
					* (y - WIN_HEIGHT / 2 + wall_height / 2) / wall_height)
				* texture->img.line_length
				+ (int)(texture->width * line->wall_x)
				* (texture->img.bits_per_pixel / 8));
		tex_colour = *(unsigned int *)src;
		my_mlx_pixel_put(&mlx->img, ray_nb, y, tex_colour);
		y++;
	}
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
