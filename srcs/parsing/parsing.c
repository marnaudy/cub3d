/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:19:32 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/08 12:47:38 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	write_error_ret(char *error)
{
	ft_putendl_fd("Error", STDOUT_FILENO);
	ft_putendl_fd(error, STDOUT_FILENO);
	return (1);
}

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
		return (write_error_ret("double identifier"));
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

void	set_player_pos(t_player *player, int x, int y, char dir)
{
	if (dir == 'N')
		player->dir_y = -1.0;
	if (dir == 'S')
		player->dir_y = 1.0;
	if (dir == 'E')
		player->dir_x = 1.0;
	if (dir == 'W')
		player->dir_x = -1.0;
	player->x = x + 0.5;
	player->y = y + 0.5;
	player->plane_x = -player->dir_y * SQRT3_6;
	player->plane_y = player->dir_x * SQRT3_6;
}

int	find_player(t_player *player, t_map *map)
{
	int	x;
	int	y;
	int	player_found;

	y = 0;
	player_found = 0;
	while (y < map->n_lin)
	{
		x = 0;
		while (x < map->n_col)
		{
			if (ft_is_in_charset(map->map[y * map->n_col + x], "NSEW"))
			{
				if (player_found)
					return (1);
				player_found = 1;
				set_player_pos(player, x, y, map->map[y * map->n_col + x]);
				map->map[y * map->n_col + x] = '0';
			}
			x++;
		}
		y++;
	}
	return (!player_found);
}

int	parse_file_map(int fd, t_map *map, int *line_count)
{
	char	*premap;

	premap = read_map(fd, line_count);
	if (!premap)
		return (1);
	get_map_size(map, premap);
	if (convert_premap_map(map, premap))
	{
		free(premap);
		return (1);
	}
	free(premap);
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

int	valid_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->n_lin)
	{
		x = 0;
		while (x < map->n_col)
		{
			if ((x == 0 || x == map->n_col - 1 || y == 0 || y == map->n_lin - 1)
				&& map->map[y * map->n_col + x] == '0')
			{
				write_error_ret("map not surrounded by walls");
				return (0);
			}
			if (map->map[y * map->n_col + x] == ' ' && touches_zero(map, x, y))
			{
				write_error_ret("map not surrounded by walls");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	parse(int argc, char **argv, t_map *map, t_player *player)
{
	int	fd;
	int	line_count;

	if (argc != 2)
		return (write_error_ret("wrong number of arguments"));
	if (check_filename(argv[1]))
		return (write_error_ret("wrong file extension"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (write_error_ret("can't open file"));
	line_count = 0;
	if (parse_file_id(fd, map, &line_count)
		|| parse_file_map(fd, map, &line_count))
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (find_player(player, map))
		return (write_error_ret("wrong number of players"));
	return (!valid_map(map));
}
