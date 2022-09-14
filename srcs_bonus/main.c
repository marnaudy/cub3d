/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:41:49 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/14 15:03:38 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
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
	new_frame(&bundle->mlx, &bundle->player, &bundle->map);
	mlx_hook(bundle->mlx.win_ptr, KeyPress, KeyPressMask,
		deal_key_press, bundle);
	mlx_hook(bundle->mlx.win_ptr, KeyRelease, KeyReleaseMask,
		deal_key_release, bundle);
	mlx_hook(bundle->mlx.win_ptr, DestroyNotify, NoEventMask,
		exit_cube, bundle);
	mlx_hook(bundle->mlx.win_ptr, MotionNotify, PointerMotionMask,
		deal_mouse_move, bundle);
	XWarpPointer(bundle->mlx.mlx_ptr->display, 0, bundle->mlx.mlx_ptr->root,
		0, 0, 0, 0, WIN_WIDTH / 2, WIN_HEIGHT - 10);
	mlx_loop_hook(bundle->mlx.mlx_ptr, update, bundle);
	mlx_loop(bundle->mlx.mlx_ptr);
	close_mlx(&bundle->mlx, &bundle->map);
	free_map(&bundle->map);
}

int	main(int argc, char **argv)
{
	t_bundle	bundle;

	init_map(&bundle.map);
	init_player(&bundle.player);
	if (parse(argc, argv, &bundle.map, &bundle.player))
		return (1);
	if (start_mlx(&bundle.mlx))
	{
		free_map(&bundle.map);
		return (1);
	}
	if (load_all_textures(&bundle.mlx, &bundle.map))
	{
		free_map(&bundle.map);
		close_mlx(&bundle.mlx, &bundle.map);
		return (1);
	}
	launch_loop(&bundle);
	return (0);
}
