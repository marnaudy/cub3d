/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:19:32 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/07 15:07:03 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

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
		if (map->north_text_name)
			return (1);
		map->north_text_name = tex_file;
	}
	if (!ft_strncmp(line, "SO", 2))
	{
		if (map->south_text_name)
			return (1);
		map->south_text_name = tex_file;
	}
	if (!ft_strncmp(line, "EA", 2))
	{
		if (map->east_text_name)
			return (1);
		map->east_text_name = tex_file;
	}
	if (!ft_strncmp(line, "WE", 2))
	{
		if (map->west_text_name)
			return (1);
		map->west_text_name = tex_file;
	}
	return (0);
}

int	parse_line_texture(t_map *map, char *line)
{
	int		i;
	char	*tex_file;

	i = 2;
	if (!ft_is_whitespace(line[2]))
		return (1);
	while (ft_is_whitespace(line[i]) && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		return (1);
	tex_file = ft_strdup(&line[i]);
	if (!tex_file)
		return (1);
	tex_file[ft_strlen(tex_file) - 1] = '\0';
	return (attribute_tex_file(map, line, tex_file));
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
		return (1);
	if (read_colours(line, &colour))
		return (1);
	if ((line[0] == 'C' && map->ceiling) || (line [0] == 'F' && map->floor))
		return (1);
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
	return (1);
}

int	parse_file_id(int fd, t_map *map, int *line_count)
{
	char	*line;
	int		nb_id;

	nb_id = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_count++;
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
	return (1);
}

int	parse(int argc, char **argv, t_map *map, t_player *player)
{
	int	fd;
	int	line_count;

	if (argc != 2)
		return (1);
	if (check_filename(argv[1]))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	line_count = 0;
	if (parse_file_id(fd, map, &line_count))
		return (1);
	(void) player;
	return (0);
}
