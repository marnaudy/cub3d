/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:45:53 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/14 15:21:25 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_map_line(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n' || line[0] == '\0')
	{
		write_error_ret("empty line in map");
		return (0);
	}
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		if (!ft_is_in_charset(line[i], "01NSEW "))
		{
			write_error_ret("invalid character in map");
			return (0);
		}
		i++;
	}
	return (1);
}

char	*add_line_to_premap(char *premap, char *line)
{
	if (!valid_map_line(line))
	{
		free(premap);
		free(line);
		return (NULL);
	}
	premap = ft_strcat(premap, line);
	if (!premap)
	{
		write_error_ret("malloc error");
		return (NULL);
	}
	return (premap);
}

char	*read_map(int fd, int *line_count)
{
	char	*premap;
	char	*line;

	premap = NULL;
	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		(*line_count)++;
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		write_error_ret("missing map");
		return (premap);
	}
	while (line)
	{
		(*line_count)++;
		premap = add_line_to_premap(premap, line);
		if (!premap)
			return (NULL);
		line = get_next_line(fd);
	}
	return (premap);
}

void	get_map_size(t_map *map, char *premap)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = 0;
	map->n_col = 0;
	map->n_lin = 0;
	while (premap[i])
	{
		if (premap[i] == '\n')
		{
			if (line_len > map->n_col)
				map->n_col = line_len;
			line_len = 0;
			map->n_lin++;
		}
		else
			line_len++;
		i++;
	}
	if (premap[i - 1] != '\n')
		map->n_lin++;
}

int	convert_premap_map(t_map *map, char *premap)
{
	int	x;
	int	y;
	int	idx;

	y = -1;
	idx = 0;
	map->map = malloc(map->n_col * map->n_lin * sizeof(char));
	if (!map->map)
		return (write_error_ret("malloc error"));
	while (++y < map->n_lin)
	{
		x = 0;
		while (premap[idx] && premap[idx] != '\n')
		{
			map->map[y * map->n_col + x] = premap[idx];
			idx++;
			x++;
		}
		idx++;
		x--;
		while (++x < map->n_col)
			map->map[y * map->n_col + x] = ' ';
	}
	return (0);
}
