/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:09:03 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/09 17:21:27 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#define FRAME_C 0x00FF0000	
#define PLAYER_C 0xFF0000

void	draw_minimap_frame(t_mlx *mlx, t_map *map, double size_ratio)
{
	int	i;
	int	x_max;
	int	y_max;

	x_max = map->n_col * size_ratio;
	y_max = map->n_lin * size_ratio;
	i = 0;
	while (i <= x_max + 1)
	{
		my_mlx_pixel_put(&mlx->img, i, 0, FRAME_C);
		my_mlx_pixel_put(&mlx->img, i, y_max + 1, FRAME_C);
		i++;
	}
	i = 0;
	while (i <= y_max + 1)
	{
		my_mlx_pixel_put(&mlx->img, 0, i, FRAME_C);
		my_mlx_pixel_put(&mlx->img, x_max + 1, i, FRAME_C);
		i++;
	}
}

void	draw_maze(t_mlx *mlx, t_map *map, double size_ratio)
{
	struct s_point	p;

	p.x = 0;
	while (p.x < map->n_col)
	{
		p.y = 0;
		while (p.y < map->n_lin)
		{
			draw_square(mlx, map, &p, size_ratio);
			p.y++;
		}
		p.x++;
	}
}

void	draw_player(t_mlx *mlx, t_player *player, double size_ratio)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = player->x * size_ratio + 1;
	y = player->y * size_ratio + 1;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			my_mlx_pixel_put(&mlx->img, x + i, y + j, PLAYER_C);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_mlx *mlx, t_player *player, t_map *map)
{
	double	size_ratio;
	int		mini_m_w;
	int		mini_m_h;

	mini_m_w = WIN_WIDTH / 5;
	mini_m_h = WIN_HEIGHT / 5;
	size_ratio = (mini_m_w - 2) / map->n_col;
	if ((mini_m_h - 2) / map->n_lin < size_ratio)
		size_ratio = (mini_m_h - 2) / map->n_lin;
	if (size_ratio < 2)
		return ;
	draw_minimap_frame(mlx, map, size_ratio);
	draw_maze(mlx, map, size_ratio);
	draw_player(mlx, player, size_ratio);
}
