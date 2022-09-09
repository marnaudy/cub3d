/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:16:44 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/09 17:19:03 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

#define EMPTY_C 0x00FFFFFF
#define WALL_C 0x0
#define VOID_C 0x00606060

unsigned int	get_map_colour(t_map *map, int x, int y)
{
	char	c;

	c = map->map[y * map->n_col + x];
	if (c == '0')
		return (EMPTY_C);
	else if (c == '1')
		return (WALL_C);
	return (VOID_C);
}

void	draw_square(t_mlx *mlx, t_map *map,
			struct s_point *p, double size_ratio)
{
	int				x;
	int				y;
	unsigned int	colour;

	colour = get_map_colour(map, p->x, p->y);
	x = p->x * size_ratio + 1;
	while (x <= (p->x + 1) * size_ratio)
	{
		y = p->y * size_ratio + 1;
		while (y <= (p->y + 1) * size_ratio)
		{
			my_mlx_pixel_put(&mlx->img, x, y, colour);
			y++;
		}
		x++;
	}
}
