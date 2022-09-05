# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marnaudy <marnaudy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 17:15:05 by marnaudy          #+#    #+#              #
#    Updated: 2022/09/05 16:28:15 by marnaudy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	cub3D

NAME_B	=	cub3D_bonus

LIBFT	=	libft/libft.a

MLX		=	minilibx-linux/libmlx.a

SRCS	=	srcs/mlx/mlx_utils.c \
			main_test.c

SRCS_B	=	bibi.c

HEADERS	=	include/minishell.h

OBJS	=	${SRCS:.c=.o}

OBJS_B	=	${SRCS_B:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -I./include -I./minilibx-linux

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
