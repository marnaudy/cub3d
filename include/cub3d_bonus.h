/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:29:51 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/14 10:50:08 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

// # define SQRT3_6 0.28867513459
# define SQRT3_6 0.5
# define COS_A 0.99875026039
# define SIN_A 0.04997916927
// A = 0.05
// # define COS_B 0.99998750002
// # define SIN_B 0.00499997916
// B = 0.005
# define COS_B 0.999998
# define SIN_B 0.00199999866
// B = 0.002

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_texture
{
	t_image	img;
	int		width;
	int		height;
	char	*name;
}	t_texture;

typedef struct s_map
{
	int				n_col;
	int				n_lin;
	char			*map;
	unsigned int	ceiling;
	unsigned int	floor;
	t_texture		north_text;
	t_texture		south_text;
	t_texture		east_text;
	t_texture		west_text;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		moving_forward;
	int		moving_back;
	int		moving_right;
	int		moving_left;
	int		turning_left;
	int		turning_right;
}	t_player;

typedef struct s_mlx
{
	t_xvar	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
}	t_mlx;

enum e_dir
{
	north,
	south,
	east,
	west
};

typedef struct s_line
{
	double		distance;
	enum e_dir	type;
	double		wall_x;
}	t_line;

typedef struct s_ray_calc
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	camera_x;
	double	dist_x;
	double	dist_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
}	t_ray_calc;

typedef struct s_bundle
{
	t_player	*player;
	t_mlx		*mlx;
	t_map		*map;
}	t_bundle;

struct s_point
{
	int	x;
	int	y;
};

void	close_mlx(t_mlx *mlx, t_map *map);
int		start_mlx(t_mlx *mlx);
int		new_frame(t_mlx *mlx, t_player *player, t_map *map);
int		deal_key_press(int keycode, t_bundle *bundle);
int		deal_key_release(int keycode, t_bundle *bundle);
int		update(t_bundle *bundle);
void	free_map(t_map *map);
int		exit_cube(t_bundle *bundle);
void	init_player(t_player *player);
void	init_map(t_map *map);
int		parse(int argc, char **argv, t_map *map, t_player *player);
int		write_error_ret(char *error);
int		load_all_textures(t_mlx *mlx, t_map *map);

void	move_up(t_player *player, t_map *map);
void	move_down(t_player *player, t_map *map);
void	move_right(t_player *player, t_map *map);
void	move_left(t_player *player, t_map *map);
void	turn_right(t_player *player);
void	turn_left(t_player *player);
void	small_turns_left(t_player *player, int n);
void	small_turns_right(t_player *player, int n);
int		deal_mouse_move(int x, int y, t_bundle *bundle);

int		check_filename(char *name);
int		id_is_texture(char *line);
int		id_is_colour(char *line);
int		attribute_tex_file(t_map *map, char *line, char *tex_file);
int		touches_zero(t_map *map, int x, int y);
int		parse_file_id(int fd, t_map *map, int *line_count);
char	*read_map(int fd, int *line_count);
void	get_map_size(t_map *map, char *premap);
int		convert_premap_map(t_map *map, char *premap);

void	init_ray_data(t_player *player, int ray_nb, t_ray_calc *data);
void	init_step_delta(t_player *player, t_ray_calc *data);
void	cast_dda(t_map *map, t_ray_calc *data, t_line *line);
void	calc_line_x(t_player *player, t_ray_calc *data, t_line *line);
void	calc_line_y(t_player *player, t_ray_calc *data, t_line *line);
void	cast_ray(t_player *player, t_map *map, int ray_nb, t_line *line);
void	my_mlx_pixel_put(t_image *img, int x, int y, unsigned int colour);
void	draw_line(t_mlx *mlx, t_map *map, t_line *line, int ray_nb);
void	draw_square(t_mlx *mlx, t_map *map,
			struct s_point *p, double size_ratio);
void	draw_minimap(t_mlx *mlx, t_player *player, t_map *map);

#endif
