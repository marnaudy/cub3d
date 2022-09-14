/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:42:38 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/14 15:21:49 by cboudrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_line_texture(t_map *map, char *line)
{
	int		i;
	char	*tex_file;

	i = 2;
	if (!ft_is_whitespace(line[2]))
		return (write_error_ret("invalid identifier"));
	while (ft_is_whitespace(line[i]) && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		return (write_error_ret("invalid identifier"));
	tex_file = ft_strdup(&line[i]);
	if (!tex_file)
		return (write_error_ret("malloc error"));
	tex_file[ft_strlen(tex_file) - 1] = '\0';
	if (attribute_tex_file(map, line, tex_file))
	{
		free(tex_file);
		return (write_error_ret("double identifier"));
	}
	return (0);
}

int	read_colours(char *line, unsigned int *colour)
{
	int	i;

	i = 2;
	if (ft_atoi(&line[i]) < 0 || ft_atoi(&line[i]) > 255)
		return (1);
	*colour = (unsigned) ft_atoi(&line[1]) << 16;
	while (line[i] != ',' && line[i])
		i++;
	if (line[i] != ',')
		return (1);
	i++;
	if (ft_atoi(&line[i]) < 0 || ft_atoi(&line[i]) > 255)
		return (1);
	*colour += (unsigned) ft_atoi(&line[i]) << 8;
	while (line[i] != ',' && line[i])
		i++;
	if (line[i] != ',')
		return (1);
	i++;
	if (ft_atoi(&line[i]) < 0 || ft_atoi(&line[i]) > 255)
		return (1);
	*colour += (unsigned) ft_atoi(&line[i]);
	return (0);
}

int	parse_line_colour(t_map *map, char *line)
{
	unsigned int	colour;

	if (!ft_is_whitespace(line[1]))
		return (write_error_ret("invalid identifier"));
	if (read_colours(line, &colour))
		return (write_error_ret("invalid or missing RGB value"));
	if ((line[0] == 'C' && map->ceiling) || (line [0] == 'F' && map->floor))
		return (write_error_ret("double identifier"));
	if (line[0] == 'C')
		map->ceiling = colour;
	else
		map->floor = colour;
	return (0);
}

int	parse_line_id(t_map *map, char *line)
{
	if (id_is_texture(line))
		return (parse_line_texture(map, line));
	if (id_is_colour(line))
		return (parse_line_colour(map, line));
	return (write_error_ret("invalid identifier"));
}

int	parse_file_id(int fd, t_map *map, int *line_count)
{
	char	*line;
	int		nb_id;

	nb_id = 0;
	line = get_next_line(fd);
	while (line)
	{
		(*line_count)++;
		if (line[0] != '\n')
		{
			if (parse_line_id(map, line))
			{
				free(line);
				return (1);
			}
			nb_id++;
		}
		free(line);
		if (nb_id == 6)
			return (0);
		line = get_next_line(fd);
	}
	return (write_error_ret("missing identifier"));
}
