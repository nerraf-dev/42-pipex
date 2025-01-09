# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 11:30:00 by sfarren           #+#    #+#              #
#    Updated: 2025/01/06 16:48:14 by sfarren          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	CC = gcc
else
	CC = clang
endif
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I$(INCLUDE_DIR)

NAME = pipex
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
INCLUDE_DIR = include
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
GNL_DIR = $(LIB_DIR)/gnl
GNL = $(GNL_DIR)/libgnl.a

SRC_FILES = pipex.c pipe.c files.c cmds.c paths.c processes.c utils.c split.c
SRC = $(foreach file, $(SRC_FILES), $(SRC_DIR)/$(file))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Build ALL
all: $(LIBFT) $(NAME)

# Build libft
$(LIBFT):
	@echo "*** Building libft... ***"
	$(MAKE) -C $(LIBFT_DIR)
	@echo "*** Build complete: libft ***"

# Build gnl
$(GNL):
	@echo "*** Building gnl... ***"
	$(MAKE) -C $(GNL_DIR)
	@echo "*** Build complete: gnl ***"

# Build main project
$(NAME): $(OBJS) $(LIBFT) $(GNL)
	@echo "Building main project..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -L$(GNL_DIR) -lgnl
	@echo "Build complete: $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean fclean re

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
