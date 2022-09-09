/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:19:32 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/09 12:40:17 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include <unistd.h>
#include <fcntl.h>

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
