# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubeal <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/11 10:38:34 by jubeal            #+#    #+#              #
#    Updated: 2019/01/04 11:50:39 by jubeal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Binary

NAME = fdf

#Path

SRC_PATH = ./srcs/

OBJ_PATH = ./objs/

INC_PATH = ./includes/

CPPFLAGS = -I./includes/

#Name

SRC_NAME =	main.c \
			file_reader.c \
			draw_wires.c \
			movement.c \
			initialisations.c \
			aff_paral.c \
			set_color.c

OBJ_NAME = $(SRC_NAME:.c=.o)

#Files

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

#Flags

LDFLAGS = -L./libft/

LFT = -lft

CC = gcc $(CFLAGS) -g3 -fsanitize=address

CFLAGS = -Wall -Wextra -Werror

MLX = -lmlx -framework OpenGL -framework AppKit

#Rules

all: $(NAME)

$(NAME): $(OBJ)
	@make -C./libft/
	@echo "\033[34mCreation of $(NAME) ...\033[0m"
	@$(CC) $(LDFLAGS) $(LFT) $(OBJ) -o $@ $(MLX)
	@echo "\033[32m$(NAME) created\n\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CPPFLAGS) -o $@ -c $<

clean:
	@make clean -C ./libft/ 2> /dev/null
	@echo "\033[33mRemoval of .o files of $(NAME) ...\033[0m"
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[31mFiles .o deleted\n\033[0m"

fclean: clean
	@make fclean -C ./libft/
	@echo "\033[33mRemoval of $(NAME)...\033[0m"
	@rm -f $(NAME)
	@echo "\033[31mBinary $(NAME) deleted\n\033[0m"

re: fclean all

norme:
	@norminette $(SRC)
	@norminette $(INC_PATH)

push: fclean
	@cp -r Makefile srcs includes maps auteur libft git
	@git -C git add .
	@git -C git commit -m fast-push
	@git -C git push
	@cd ..

.PHONY: all, clean, fclean, re
