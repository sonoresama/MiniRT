# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eorer <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 18:32:12 by eorer             #+#    #+#              #
#    Updated: 2023/09/19 10:54:37 by eorer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I$(INC) -I./minilibx-linux

LFLAGS = -L./minilibx-linux -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd

INC = /usr/include

INCLIB = $(INC)/../lib

LIBX = libmlx_Linux.a

SRC = $(wildcard ./*.c) 

OBJ = $(SRC:.c=.o)

NAME = minirt


all : $(NAME)

$(NAME) : $(OBJ) $(LIBX)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

$(LIBX) :
	@make -C ./minilibx-linux

clean : 
	/bin/rm -f $(OBJ)

fclean : clean
	/bin/rm -f $(NAME)

re : fclean all
