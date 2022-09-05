/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:29:51 by marnaudy          #+#    #+#             */
/*   Updated: 2022/09/05 16:26:31 by marnaudy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_colour
{
	int	r;
	int	g;
	int	b;
}	t_colour;

typedef struct s_map
{
	int			n_col;
	int			n_lin;
	char		*map;
	t_colour	ceiling;
	t_colour	floor;
	t_colour	north;
	t_colour	south;
	t_colour	east;
	t_colour	west;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	cam_dir_x;
	double	cam_dir_y;
}	t_player;

typedef struct	s_img {
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

void	close_mlx(t_mlx *mlx);
int		start_mlx(t_mlx *mlx);


#endif
