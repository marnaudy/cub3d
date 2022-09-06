/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:29:51 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/06 18:02:24 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_map
{
	int				n_col;
	int				n_lin;
	char			*map;
	unsigned int	ceiling;
	unsigned int	floor;
	unsigned int	north;
	unsigned int	south;
	unsigned int	east;
	unsigned int	west;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	dir_len;
	double	plane_x;
	double	plane_y;
	int		turning_left;
	int		turning_right;
	int		moving_forward;
	int		moving_back;
}	t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
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
}	t_line;

typedef struct s_ray_calc
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	ray_dir_len;
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

void	close_mlx(t_mlx *mlx);
int		start_mlx(t_mlx *mlx);
int		new_frame(t_mlx *mlx, t_player *player, t_map *map);
int		deal_key_press(int keycode, t_bundle *bundle);
int		deal_key_release(int keycode, t_bundle *bundle);
int		update(t_bundle *bundle);
int		exit_cube(t_bundle *bundle);

#endif
