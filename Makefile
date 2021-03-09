# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paulo <paulo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 16:34:32 by pharatyk          #+#    #+#              #
#    Updated: 2021/03/09 11:26:20 by paulo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname -s)

NAME			= vil

OBJ_DIR			= ./vil_obj/

SRC_VIL_DIR	= ./vil_src/villikottur_src/
ifeq ($(OS), Linux)
SRC_VIL		=	vil_detector.c\
				vil.c\
				vil_printer.c\
				vil_tools.c\
				wooder.c\
				vil_tools_linux.c
endif
ifeq ($(OS), Darwin)
SRC_VIL		=	vil_detector.c\
				vil.c\
				vil_printer.c\
				vil_tools.c\
				wooder.c\
				vil_tools_darwin.c
endif


SRCS		    = $(addprefix $(SRC_VIL_DIR), $(SRC_VIL))

OBJ				= $(addprefix $(OBJ_DIR), $(SRC_VIL:.c=.o))

CC				= gcc -g #-Wall -Wextra -Werror -Wuninitialized
CFLAGS			= -I ./libft/includes -I ./vil_inc

all: $(NAME)

$(NAME): lib $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) libft/libft.a
	@printf " _/\nseekat [done]\n"

lib:
	@make -C ./libft/

clean:
	@make clean -C ./libft/
	@rm -f $(OBJ)
	@printf "clean  [done]\n"

fclean: clean
	@make fclean -C ./libft/
	@rm -f $(NAME)
	@printf "fclean [done]\n"

$(OBJ_DIR)%.o: $(SRC_VIL_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@printf ">"
	@$(CC) -c $(CFLAGS) $< -o $@

re: fclean all

.PHONY: all clean fclean re lib $(NAME)

