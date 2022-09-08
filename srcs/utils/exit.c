/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:59:11 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/08 12:04:44 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	free_map(t_map *map)
{
	free(map->north_text.name);
	free(map->south_text.name);
	free(map->east_text.name);
	free(map->west_text.name);
	free(map->map);
}

int	exit_cube(t_bundle *bundle)
{
	close_mlx(bundle->mlx, bundle->map);
	free_map(bundle->map);
	exit(0);
}
