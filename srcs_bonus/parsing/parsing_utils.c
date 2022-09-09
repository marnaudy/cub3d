/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:40:19 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/09 12:40:09 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_filename(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5)
		return (1);
	if (ft_strcmp(&name[len - 4], ".cub"))
		return (1);
	if (name[len - 5] == '/')
		return (1);
	return (0);
}

int	id_is_texture(char *line)
{
	return (!ft_strncmp(line, "NO", 2)
		|| !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "EA", 2)
		|| !ft_strncmp(line, "WE", 2));
}

int	id_is_colour(char *line)
{
	return (line[0] == 'F' || line[0] == 'C');
}

int	attribute_tex_file(t_map *map, char *line, char *tex_file)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		if (map->north_text.name)
			return (1);
		map->north_text.name = tex_file;
	}
	if (!ft_strncmp(line, "SO", 2))
	{
		if (map->south_text.name)
			return (1);
		map->south_text.name = tex_file;
	}
	if (!ft_strncmp(line, "EA", 2))
	{
		if (map->east_text.name)
			return (1);
		map->east_text.name = tex_file;
	}
	if (!ft_strncmp(line, "WE", 2))
	{
		if (map->west_text.name)
			return (1);
		map->west_text.name = tex_file;
	}
	return (0);
}

int	touches_zero(t_map *map, int x, int y)
{
	if (x > 0 && map->map[y * map->n_col + x - 1] == '0')
		return (1);
	if (x < map->n_col - 1 && map->map[y * map->n_col + x + 1] == '0')
		return (1);
	if (y > 0 && map->map[(y - 1) * map->n_col + x] == '0')
		return (1);
	if (y < map->n_lin - 1 && map->map[(y + 1) * map->n_col + x] == '0')
		return (1);
	return (0);
}
