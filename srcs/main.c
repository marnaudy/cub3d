/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:41:49 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/09 14:43:06 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/X.h>
#include <unistd.h>

int	write_error_ret(char *error)
{
	ft_putendl_fd("Error", STDOUT_FILENO);
	ft_putendl_fd(error, STDOUT_FILENO);
	return (1);
}

void	launch_loop(t_bundle *bundle)
{
	new_frame(bundle->mlx, bundle->player, bundle->map);
	mlx_hook(bundle->mlx->win_ptr, KeyPress, KeyPressMask,
		deal_key_press, bundle);
	mlx_hook(bundle->mlx->win_ptr, KeyRelease, KeyReleaseMask,
		deal_key_release, bundle);
	mlx_hook(bundle->mlx->win_ptr, DestroyNotify, NoEventMask,
		exit_cube, bundle);
	mlx_loop_hook(bundle->mlx->mlx_ptr, update, bundle);
	mlx_loop(bundle->mlx->mlx_ptr);
	close_mlx(bundle->mlx, bundle->map);
	free_map(bundle->map);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_player	player;
	t_mlx		mlx;
	t_bundle	bundle;

	init_map(&map);
	init_player(&player);
	if (parse(argc, argv, &map, &player))
		return (1);
	bundle.mlx = &mlx;
	bundle.map = &map;
	bundle.player = &player;
	if (start_mlx(&mlx))
	{
		free_map(&map);
		return (1);
	}
	if (load_all_textures(&mlx, &map))
	{
		free_map(&map);
		close_mlx(&mlx, &map);
		return (1);
	}
	launch_loop(&bundle);
	return (0);
}
