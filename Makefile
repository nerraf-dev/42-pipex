# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 11:30:00 by sfarren           #+#    #+#              #
#    Updated: 2025/04/01 14:55:45 by sfarren          ###   ########.fr        #
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
# TODO: Change bonus name: remove _bonus
BONUS_NAME = pipex_bonus
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
INCLUDE_DIR = include
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_FILES = pipex.c \
			pipe.c \
			files.c \
			cmds.c \
			paths.c \
			processes.c \
			utils.c \
			split.c

BONUS_SRC_FILES = pipex_bonus.c \
					utils_bonus.c \
					pipe.c \
					files.c \
					cmds_bonus.c \
					paths.c \
					processes.c \
					utils.c \
					split.c

SRC = $(foreach file, $(SRC_FILES), $(SRC_DIR)/$(file))
BONUS_SRC = $(foreach file, $(BONUS_SRC_FILES), $(SRC_DIR)/$(file))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
BONUS_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(BONUS_SRC))

# Build ALL
all: $(LIBFT) $(NAME)

# Build BONUS
bonus: $(LIBFT) $(BONUS_NAME)

# Build libft
$(LIBFT):
	@echo "*** Building libft... ***"
	$(MAKE) -C $(LIBFT_DIR)
	@echo "*** Build complete: libft ***"

# Build main project
$(NAME): $(OBJS) $(LIBFT)
	@echo "Building main project..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft
	@echo "Build complete: $(NAME)"

# Build bonus project
$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	@echo "Building bonus project..."
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft
	@echo "Build complete: $(BONUS_NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean fclean re bonus

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(BONUS_OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
