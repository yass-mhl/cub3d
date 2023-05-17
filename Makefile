# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 18:35:00 by gregoire          #+#    #+#              #
#    Updated: 2023/05/17 15:30:40 by ymehlil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = main.c \
      parsing_args.c \
	  parsing_map.c \
	  utils_parsing.c \
      raycasting.c \
      utils.c \
      player_movement.c \
      rendering.c \
      exit.c \
	  check.c

SRCSD	= srcs/

OBJSD	= objs/

GNL_PATH	= get_next_line/
GNL_SRCS	= get_next_line.c get_next_line_utils.c 
GNL_OBJS	= $(addprefix $(OBJSD), $(GNL_SRCS:.c=.o))
OBJS	= $(addprefix $(OBJSD), $(SRCS:.c=.o))

LIBFT_A	= libft/libft.a
PRINTF_A = ft_printf/libftprintf.a
MINILIBX_A = minilibx-linux/libmlx.a

CC = cc
RM	= rm -rf
FLAGS = -Wall -Wextra -Werror -g -I/usr/include -Imlx_linux -O3 -Iincludes -g3
LIB = -L/usr/include -lreadline -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz

# Couleurs
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m

all: $(NAME)

$(LIBFT_A):
	@echo "$(YELLOW)Compilation de libft...$(RESET)"
	@make -C libft > /dev/null
	@echo "$(GREEN)Libft compilé avec succès!$(RESET)"

$(PRINTF_A):
	@echo "$(YELLOW)Compilation de ft_printf...$(RESET)"
	@make -C ft_printf > /dev/null
	@echo "$(GREEN)Ft_printf compilé avec succès!$(RESET)"

$(MINILIBX_A):
	@echo "$(YELLOW)Compilation de minilibx...$(RESET)"
	@make -C minilibx-linux > /dev/null
	@echo "$(GREEN)Minilibx compilé avec succès!$(RESET)"

$(NAME): $(OBJS) $(PRINTF_A) $(GNL_OBJS) $(LIBFT_A) $(MINILIBX_A)
	@$(CC) $(FLAGS) -o $@ $^ $(LIB) > /dev/null
	@echo "$(CYAN)[$(NAME)]$(RESET) $(GREEN)Liaison des objets réussie.$(RESET)"

$(OBJSD)%.o: $(SRCSD)%.c
	@mkdir -p $(dir $@) > /dev/null
	@echo "$(CYAN)[$@]$(RESET) $(BLUE)Compilation...$(RESET)" 
	@$(CC) $(FLAGS) -c -o $@ $< > /dev/null

$(OBJSD)%.o: $(GNL_PATH)%.c
	@echo "$(CYAN)[$@]$(RESET) $(BLUE)Compilation...$(RESET)"
	@$(CC) $(FLAGS) -c -o $@ $< > /dev/null

clean:
	@rm -rf $(OBJSD) > /dev/null
	@make -C libft clean > /dev/null
	@make -C ft_printf clean > /dev/null
	@make -C minilibx-linux clean > /dev/null
	@echo "$(MAGENTA)Suppression des fichiers objets terminée.$(RESET)"

fclean: clean
	@make -C ft_printf fclean > /dev/null
	@make -C minilibx-linux clean > /dev/null
	@rm -rf $(NAME) > /dev/null
	@echo "$(MAGENTA)Nettoyage complet effectué.$(RESET)"
	
re: fclean all

.PHONY: all clean fclean re
