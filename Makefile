# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cboudrin <cboudrin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 17:15:05 by marnaudy          #+#    #+#              #
#    Updated: 2022/09/14 15:24:50 by cboudrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	cub3D

NAME_B	=	cub3D_bonus

LIBFT	=	libft/libft.a

MLX		=	minilibx-linux/libmlx.a

SRCS	=	srcs/mlx/mlx_utils.c \
			srcs/raycasting/cast_utils.c \
			srcs/raycasting/draw_ray.c \
			srcs/raycasting/raycasting.c \
			srcs/interactive/movement_utils.c \
			srcs/interactive/movement.c \
			srcs/utils/exit.c \
			srcs/utils/init.c \
			srcs/parsing/parsing_utils.c \
			srcs/parsing/id_parsing.c \
			srcs/parsing/read_map.c \
			srcs/parsing/parsing.c \
			srcs/main.c

SRCS_B	=	srcs_bonus/mlx/mlx_utils.c \
			srcs_bonus/raycasting/cast_utils.c \
			srcs_bonus/raycasting/minimap_utils.c \
			srcs_bonus/raycasting/draw_minimap.c \
			srcs_bonus/raycasting/draw_ray.c \
			srcs_bonus/raycasting/raycasting.c \
			srcs_bonus/interactive/movement_utils.c \
			srcs_bonus/interactive/movement_utils2.c \
			srcs_bonus/interactive/movement.c \
			srcs_bonus/utils/exit.c \
			srcs_bonus/utils/init.c \
			srcs_bonus/parsing/parsing_utils.c \
			srcs_bonus/parsing/id_parsing.c \
			srcs_bonus/parsing/read_map.c \
			srcs_bonus/parsing/parsing.c \
			srcs_bonus/main.c

HEADERS	=	include/cub3d.h \
			include/cub3d_bonus.h

OBJS	=	${SRCS:.c=.o}

OBJS_B	=	${SRCS_B:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -I./libft -I./include -I./minilibx-linux

RM		=	rm -f

all:		${NAME}

${NAME}:	${OBJS} ${LIBFT} ${MLX}
			${CC} ${OBJS} ${LIBFT} ${MLX} -lXext -lX11 -lm -o ${NAME}

bonus:		${OBJS_B} ${LIBFT} ${MLX}
			${CC} ${OBJS_B} ${LIBFT} ${MLX} -lXext -lX11 -lm -o ${NAME_B}

${LIBFT}:
			make -C libft

${MLX}:
			make -C minilibx-linux

%.o:		%.c	${HEADERS}
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			${RM} ${OBJS} ${OBJS_B}
			make -C libft clean

fclean:		clean
			${RM} ${NAME} ${NAME_B} ${LIBFT}

re:			fclean all

.PHONY:		all clean fclean re
