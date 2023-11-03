# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blerouss <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 15:06:04 by blerouss          #+#    #+#              #
#    Updated: 2023/10/31 12:48:47 by eorer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=leak

SRC = 	src/parsing/check_file.c		\
	src/parsing/ft_clear_all.c		\
	src/parsing/ft_fill_atmos.c		\
	src/parsing/ft_fill_camera.c		\
	src/parsing/ft_fill_cylinder.c		\
	src/parsing/ft_fill_light.c		\
	src/parsing/ft_fill_plan.c		\
	src/parsing/ft_fill_sphere.c		\
	src/parsing/ft_fill_vector.c		\
	src/parsing/ft_init_data.c		\
	src/parsing/ft_print_all.c		\
	src/parsing/parsing.c			\
	src/utils/ft_calloc.c			\
	src/utils/ft_clear_gnl.c		\
	src/utils/ft_strncmp.c			\
	src/utils/ft_free_tab.c			\
	src/utils/ft_split.c			\
	src/utils/ft_split_2_separator.c	\
	src/utils/ft_atod.c			\
	src/utils/ft_atoi.c			\
	src/utils/ft_strlen.c			\
	src/utils/get_next_line.c		\
	src/utils/get_next_line_utils.c		\
	src/utils/utils.c			\
	src/utils/maths_utils.c 		\
	src/utils/mlx_utilities.c		\
	src/utils/normal_vector.c		\
	src/exec/draw_scene.c			\
	src/exec/sphere.c			\
	src/exec/get_closest_plan.c		\
	src/exec/get_closest_cylinder.c		\
	src/exec/is_hiting_object.c		\
	src/exec/get_form_color.c		\
	src/exec/ray.c				\
	src/exec/ray_color.c			\
	src/main.c
#	src/tito/camera.c\
#	src/tito/color.c \
#	src/tito/init.c \
#	src/tito/ray.c \
#	src/tito/scene.c \
#	src/tito/sphere.c 
	

INC =	inc/				\


MLX_FILE	=	libmlx_Linux.a

MLX_FLAG	=	-lX11 -lXext -lm -lbsd

MLX_PATH	=	./minilibx-linux/

MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))

MLX_EX		=	$(MLX_LIB) $(MLX_FLAG)

OBJ = $(SRC:.c=.o)

all : $(NAME)	

$(MLX_FILE):
	make -sC $(MLX_PATH)

$(NAME): $(MLX_FILE) $(OBJ)
	$(CC) -g $(CFLAGS) $(OBJ) -lm -I $(INC)  $(MLX_EX) -o $(NAME)

clean:
	make clean -sC $(MLX_PATH)
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re : fclean all
