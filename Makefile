OS := $(shell uname -s)

NAME			=	vil

OBJ_DIR			=	./vil_obj/

SRC_SEEKAT_DIR	=	./vil_src/seekat_src/
SRC_INFECT_DIR	=	./vil_src/infect_src/

ifeq ($(OS), Linux)
SRC_SEEKAT		=	seekat_detector.c\
					seekat.c\
					seekat_printer.c\
					seekat_tools.c\
					seekat_sonar.c\
					seekat_flags.c\
					seekat_tools_linux.c
endif
ifeq ($(OS), Darwin)
SRC_SEEKAT		=	seekat_detector.c\
					seekat.c\
					seekat_printer.c\
					seekat_tools.c\
					seekat_sonar.c\
					seekat_flags.c\
					seekat_tools_darwin.c
endif

SRC_INFECT		=	wooder.c


SRCS		    =	$(addprefix $(SRC_SEEKAT_DIR), $(SRC_SEEKAT))\
					$(addprefix $(SRC_INFECT_DIR), $(SRC_INFECT))

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC_SEEKAT:.c=.o))\
					$(addprefix $(OBJ_DIR), $(SRC_INFECT:.c=.o))

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

$(OBJ_DIR)%.o: $(SRC_SEEKAT_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@printf ">"
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)%.o: $(SRC_INFECT_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@printf ">"
	@$(CC) -c $(CFLAGS) $< -o $@

re: fclean all

.PHONY: all clean fclean re lib $(NAME)

