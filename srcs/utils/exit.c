/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:59:11 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/07 16:14:29 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

int	exit_cube(t_bundle *bundle)
{
	close_mlx(bundle->mlx);
	free(bundle->map->north_text_name);
	free(bundle->map->south_text_name);
	free(bundle->map->east_text_name);
	free(bundle->map->west_text_name);
	free(bundle->map->map);
	exit(0);
}
