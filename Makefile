OS := $(shell uname -s)

NAME			=	vil

OBJ_DIR			=	./vil_obj/EXE/
PARA_OBJ_DIR	=	./vil_obj/PARASITE/

SRC_SEEKAT_DIR	=	./vil_src/seekat_src/
SRC_INFECT_DIR	=	./vil_src/infect_src/
SRC_TOOLS_DIR	=	./vil_src/tools/
SRC_ASM_DIR		=	./vil_src/asm_src/

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

SRC_INFECT		=	wooder.c\
					wooder_tools.c\
					wooder_64stuff.c

SRC_TOOLS		=	signals.c

SRC_ASM			=	hello.asm

SRC_PARASITE	=	parasite.asm

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC_SEEKAT:.c=.o))\
					$(addprefix $(OBJ_DIR), $(SRC_INFECT:.c=.o))\
					$(addprefix $(OBJ_DIR), $(SRC_TOOLS:.c=.o))\
					$(addprefix $(OBJ_DIR), $(SRC_ASM:.asm=.o))

PARASITE_OBJ	=	$(addprefix $(PARA_OBJ_DIR), $(SRC_PARASITE:.asm=.bin))

CC				=	gcc #-g #-Wall -Wextra -Werror -Wuninitialized
CFLAGS			=	-I ./vil_inc

all: $(NAME)

$(NAME): $(OBJ) $(PARASITE_OBJ)
	@$(CC) -o $(NAME) $(OBJ)
	@printf " _/\nseekat [done]\n"

clean:
	@rm -f $(OBJ)
	@printf "clean  [done]\n"

fclean: clean
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

$(OBJ_DIR)%.o: $(SRC_TOOLS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@printf ">"
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)%.o: $(SRC_ASM_DIR)%.asm
	@mkdir -p $(OBJ_DIR)
	@printf ">"
	@nasm -f elf64 $< -o $@

$(PARA_OBJ_DIR)%.bin: $(SRC_ASM_DIR)%.asm
	@mkdir -p $(PARA_OBJ_DIR)
	@printf ">"
	@nasm -f bin $< -o $@
re: fclean all

.PHONY: all clean fclean re lib $(NAME)

