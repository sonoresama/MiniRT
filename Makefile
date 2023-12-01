# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blerouss <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 15:06:04 by blerouss          #+#    #+#              #
#    Updated: 2023/12/01 13:46:45 by eorer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

BONUS = miniRT_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=leak

SRC = 	src/parsing/check_file.c			\
		src/parsing/ft_clear_all.c			\
		src/parsing/ft_fill_atmos.c			\
		src/parsing/ft_fill_camera.c		\
		src/parsing/ft_fill_cylinder.c		\
		src/parsing/ft_fill_light.c			\
		src/parsing/ft_fill_plan.c			\
		src/parsing/ft_fill_sphere.c		\
		src/parsing/ft_fill_vector.c		\
		src/parsing/ft_init_data.c			\
		src/parsing/ft_count_separator.c	\
		src/parsing/parsing.c				\
		src/utils/ft_calloc.c				\
		src/utils/ft_clear_gnl.c			\
		src/utils/ft_strncmp.c				\
		src/utils/ft_free_tab.c				\
		src/utils/ft_split.c				\
		src/utils/ft_split_2_separator.c	\
		src/utils/ft_atod.c					\
		src/utils/ft_atoi.c					\
		src/utils/ft_strlen.c				\
		src/utils/ft_tablen.c				\
		src/utils/get_next_line.c			\
		src/utils/get_next_line_utils.c		\
		src/utils/utils.c					\
		src/utils/maths_utils.c 			\
		src/utils/maths_utils2.c 			\
		src/utils/maths_utils3.c 			\
		src/utils/mlx_utilities.c			\
		src/utils/normal_vector.c			\
		src/exec/draw_scene.c				\
		src/exec/sphere.c					\
		src/exec/get_closest_plan.c			\
		src/exec/get_closest_cylinder.c		\
		src/exec/is_hiting_object.c			\
		src/exec/get_form_color.c			\
		src/exec/get_form_color_utils.c		\
		src/exec/light_shadow.c				\
		src/exec/ray.c						\
		src/exec/ray_color.c				\
		src/exec/cylinder_utils.c			\
		src/main.c

SRC_BONUS = bonus/parsing/check_file.c			\
			bonus/parsing/ft_clear_all.c		\
			bonus/parsing/ft_fill_atmos.c		\
			bonus/parsing/ft_fill_camera.c		\
			bonus/parsing/ft_fill_cylinder.c	\
			bonus/parsing/ft_fill_light.c		\
			bonus/parsing/ft_fill_plan.c		\
			bonus/parsing/ft_fill_sphere.c		\
			bonus/parsing/ft_fill_triangle.c	\
			bonus/parsing/ft_fill_vector.c		\
			bonus/parsing/ft_init_data.c		\
			bonus/parsing/ft_count_separator.c	\
			bonus/parsing/parsing.c				\
			bonus/utils/ft_calloc.c				\
			bonus/utils/ft_clear_gnl.c			\
			bonus/utils/ft_strncmp.c			\
			bonus/utils/ft_free_tab.c			\
			bonus/utils/ft_split.c				\
			bonus/utils/ft_split_2_separator.c	\
			bonus/utils/ft_atod.c				\
			bonus/utils/ft_atoi.c				\
			bonus/utils/ft_strlen.c				\
			bonus/utils/ft_tablen.c				\
			bonus/utils/get_next_line.c			\
			bonus/utils/get_next_line_utils.c	\
			bonus/utils/utils.c					\
			bonus/utils/maths_utils.c 			\
			bonus/utils/maths_utils2.c 			\
			bonus/utils/maths_utils3.c 			\
			bonus/utils/maths_utils4.c 			\
			bonus/utils/mlx_utilities.c			\
			bonus/utils/normal_vector.c			\
			bonus/utils/hook_tito.c			\
			bonus/utils/hook_utils.c			\
			bonus/exec/draw_scene.c				\
			bonus/exec/sphere.c					\
			bonus/exec/get_closest_plan.c		\
			bonus/exec/get_closest_cylinder.c	\
			bonus/exec/get_closest_triangle.c	\
			bonus/exec/is_hiting_object.c		\
			bonus/exec/get_form_color.c			\
			bonus/exec/get_form_color_utils.c	\
			bonus/exec/light_shadow.c			\
			bonus/exec/ray.c					\
			bonus/exec/ray_color.c				\
			bonus/exec/cylinder_utils.c			\
			bonus/main.c

INC =	inc/					\

HEADER =	./inc/define.h		\
			./inc/structures.h	\
			./inc/minirt.h	

MLX_FILE	=	libmlx_Linux.a

MLX_FLAG	=	-lX11 -lXext -lm -lbsd

MLX_PATH	=	./minilibx-linux/

MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))

MLX_EX		=	$(MLX_LIB) $(MLX_FLAG)

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)	

$(MLX_LIB):
	@make -sC $(MLX_PATH)

$(NAME) : $(MLX_LIB) $(SRC) $(OBJ) $(HEADER)
	$(CC) -g $(CFLAGS) $(OBJ) -I $(INC)  $(MLX_EX) -o $(NAME)

bonus:  $(MLX_LIB) $(SRC_BONUS) $(OBJ_BONUS) $(HEADER)
	$(CC) -g $(CFLAGS) $(OBJ_BONUS) -I $(INC)  $(MLX_EX) -o $(BONUS)

clean_m : 
	@/bin/rm -f $(OBJ)

fclean_m : clean_m
	@/bin/rm -f $(NAME)

clean_b : 
	@/bin/rm -f $(OBJ_BONUS)

fclean_b : clean_b
	@/bin/rm -f $(BONUS)

clean: clean_m clean_b

fclean: fclean_m fclean_b

re : fclean all
