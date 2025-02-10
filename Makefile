# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 13:14:15 by jtuomi            #+#    #+#              #
#    Updated: 2025/02/10 00:31:58 by marvin           \__/    i                #
#                                                                              #
# **************************************************************************** #

AR = ar rcs
CC = cc
TARGET_REPO = https://github.com/codam-coding-college/MLX42.git
INCLUDE_DIRS = libft
INCLUDE = Makefile
HEADERS	:= -Iinclude -IMLX42/include/MLX42
CFLAGS = -Wall -Wextra -Werror -O3 -ffast-math -flto $(HEADERS) -fopenmp
MLX	:= MLX42
LIBS	:= -L $(MLX)/build -lmlx42 -L libft -lft -ldl -lglfw -pthread -lm
SRC = fractol.c \
	julia.c \
	fern.c \
	mandelbrot.c \
	hook.c \
	util.c
OBJ := $(SRC:%.c=%.o)
MAKE = make -C
NAME = fractol

all: $(NAME)
$(NAME): mlx libft/libft.a $(OBJ)
	$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
libft/libft.a:
	$(MAKE) libft all supp
mlx: $(MLX)
$(MLX):
	git clone $(TARGET_REPO) $@
	cmake $(MLX) -B $(MLX)/build
	$(MAKE) $(MLX)/build -j4

clean:
	$(MAKE) libft clean
	$(MAKE) $(MLX)/build clean
	rm -f $(OBJ)
fclean: clean
	$(MAKE) libft fclean
	rm -rf $(MLX)
	rm -f $(NAME)
re: fclean all

.PHONY:
	all, libft, clean, flean, re, libmlx
