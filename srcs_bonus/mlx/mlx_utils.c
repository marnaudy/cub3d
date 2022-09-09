/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:19:57 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/09 12:39:55 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

void	close_mlx(t_mlx *mlx, t_map *map)
{
	if (map)
	{
		if (map->north_text.img.img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, map->north_text.img.img_ptr);
		if (map->south_text.img.img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, map->south_text.img.img_ptr);
		if (map->east_text.img.img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, map->east_text.img.img_ptr);
		if (map->west_text.img.img_ptr)
			mlx_destroy_image(mlx->mlx_ptr, map->west_text.img.img_ptr);
	}
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
}

int	start_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (-1);
	mlx->win_ptr
		= mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		return (-1);
	}
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img.img_ptr)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		return (-1);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr,
			&mlx->img.bits_per_pixel, &mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.addr)
		return (-1);
	return (0);
}

int	load_texture(t_texture *texture, t_mlx *mlx)
{
	texture->img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, texture->name,
			&texture->width, &texture->height);
	if (!texture->img.img_ptr)
		return (1);
	texture->img.addr = mlx_get_data_addr(texture->img.img_ptr,
			&texture->img.bits_per_pixel, &texture->img.line_length,
			&texture->img.endian);
	if (!texture->img.addr)
		return (1);
	return (0);
}

int	load_all_textures(t_mlx *mlx, t_map *map)
{
	if (load_texture(&map->north_text, mlx))
		return (write_error_ret("north texture failed"));
	if (load_texture(&map->south_text, mlx))
		return (write_error_ret("south texture failed"));
	if (load_texture(&map->east_text, mlx))
		return (write_error_ret("east texture failed"));
	if (load_texture(&map->west_text, mlx))
		return (write_error_ret("west texture failed"));
	free(map->north_text.name);
	free(map->south_text.name);
	free(map->east_text.name);
	free(map->west_text.name);
	map->north_text.name = NULL;
	map->south_text.name = NULL;
	map->east_text.name = NULL;
	map->west_text.name = NULL;
	return (0);
}
