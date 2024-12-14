# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 13:14:15 by jtuomi            #+#    #+#              #
#    Updated: 2024/12/04 15:01:31 by jtuomi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AR = ar rcs
CC = cc
INCLUDE_DIRS = libft
INCLUDE = Makefile
CFLAGS = -Wall -Wextra -Werror
LIBMLX	:= ./lib/MLX42
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a libft/libft.a -ldl -lglfw -pthread -lm
SRC = fractol.c \
	julia.c
SRCS = $(shell find ./src -iname "*.c")
SRC_FT = ft_atoi.c \
	ft_ldiv.c \
	ft_ltostr.c \
	ft_strlen.c \
	ft_printf.c \
	specifiers.c \
	more_specifiers.c
OBJ := $(SRC:%.c=%.o)
OBJS := $(addprefix libft/, :%.c=%.o) $
OBJ_ALL := $(OBJ) $(OBJS)
MAKE = make -C
NAME = fractol

all: libmlx $(NAME)
$(NAME) : $(OBJ) libft.a
	$(CC) $(CFLAGS) $(SRC) $(HEADERS) $(LIBS) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
libft.a:
	$(MAKE) libft all supp
libmlx:
ifeq ("$(wildcard ./lib/src/mlx_init.c)","" )
	git clone https://github.com/codam-coding-college/MLX42.git lib/MLX42	
endif
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
clean:
	$(MAKE) libft clean
	@rm -rf $(LIBMLX)
	rm -f $(OBJ)
fclean: clean
	$(MAKE) libft fclean
	rm -f $(NAME)
re: fclean all

.PHONY:
	all, libft, clean, flean, re, libmlx
