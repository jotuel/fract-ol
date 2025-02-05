# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 13:14:15 by jtuomi            #+#    #+#              #
#    Updated: 2024/12/23 15:45:14 by jtuomi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AR = ar rcs
CC = cc
TARGET_REPO = https://github.com/codam-coding-college/MLX42.git
INCLUDE_DIRS = libft
INCLUDE = Makefile
CFLAGS = -Wall -Wextra -Werror -Ofast
LIBMLX	:= ./libmlx
HEADERS	:= -I ./libft -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a libft/libft.a -ldl -lglfw -pthread -lm
SRC = fractol.c \
	julia.c \
	fern.c \
	mandelbrot.c
SRCS = $(shell find ./src -iname "*.c")
OBJ := $(SRC:%.c=%.o)
OBJS := $(addprefix libft/, :%.c=%.o)
OBJ_ALL := $(OBJ) $(OBJS)
MAKE = make -C
NAME = fractol

all: ./libft/libft.a ./libmlx/build/libmlx42.a $(NAME)
$(NAME): $(OBJ) ./libft/libft.a
	$(CC) $(CFLAGS) $(SRC) $(HEADERS) $(LIBS) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
./libft/libft.a:
	$(MAKE) libft all supp
./libmlx/buid/libmlx42.a:
	git clone $(TARGET_REPO) $(LIBMLX)
	cmake $(LIBMLX) -B $(LIBMLX)/build && $(MAKE) $(LIBMLX)/build -j4
clean:
	$(MAKE) libft clean
	$(MAKE) libmlx/build clean
	rm -f $(OBJ)
fclean: clean
	$(MAKE) libft fclean
	rm -f $(NAME)
re: fclean all

.PHONY:
	all, libft, clean, flean, re, libmlx
