/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:00:00 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/14 10:46:01 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

#define WALL_RATIO 1.5

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
	if (line->distance < 0.00001)
		line_height = 3000000;
	y = 0;
	while (y < WIN_HEIGHT / 2 - line_height / 2 && y < WIN_HEIGHT / 2)
	{
		my_mlx_pixel_put(&mlx->img, ray_nb, y, map->ceiling);
		y++;
	}
	y = WIN_HEIGHT;
	while (y >= line_height / 2 + WIN_HEIGHT / 2 && y >= WIN_HEIGHT / 2)
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

	wall_height = (int)(WIN_HEIGHT / line->distance) * WALL_RATIO;
	if (line->distance < 0.00001)
		wall_height = 3000000;
	draw_floor_and_ceiling(mlx, map, line, ray_nb);
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
