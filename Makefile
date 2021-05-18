SRC_DIR	:= srcs/
INC_DIR	:= inc/
OBJ_DIR	:= obj/
BIN_DIR	:= bin/

NAME	:= $(BIN_DIR)minishell
SRC		:= $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR)*/*.c)

OBJ		:= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INC	:= $(INC_DIR)minishell.h
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
INCLUDE	:= -Iinc -Ilibft/inc/
TERMCAP := -lncurses
LDFLAGS	:= -Llibft/bin -lft $(TERMCAP)
# LDFLAGS	:= -Llibft/bin -lft $(TERMCAP) -g3 -fsanitize=address


.PHONY: all clean fclean re
.SILENT:

all: lib $(NAME)
	echo "./bin/minishell \033[32mrdy 2 use\033[0m"
	echo "--------------------------------------------"
	echo ""

lib:
	make -C libft

$(NAME):  $(OBJ) libft/bin/libft.a | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@
	echo "$@ (exec) \033[32mcreated\033[0m"
	echo "--------------------------------------------"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)| $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	echo "$@ \033[32mcreated\033[0m"

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@
	echo "$(OBJ_DIR) \033[32mdir created\033[0m"

clean:
	$(RM) -rf $(OBJ_DIR)
	echo "$(OBJ_DIR) \033[31mdir deleted\033[0m"
	$(RM) libmlx.dylib
	make -C libft clean

fclean:
	$(RM) -rf $(OBJ_DIR)
	echo "$(OBJ_DIR) \033[31mdir deleted\033[0m"
	$(RM) libmlx.dylib
	$(RM) -rf $(BIN_DIR)
	echo "$(BIN_DIR) \033[31mdir deleted\033[0m"
	make -C libft fclean

fclean_re:
	make -C libft re
	$(RM) -rf $(OBJ_DIR)/*
	echo "$(OBJ_DIR)*.o \033[31mdeleted\033[0m"
	$(RM) -rf $(BIN_DIR)
	echo "$(BIN_DIR) \033[31mdir deleted\033[0m"
	echo "--------------------------------------------"

re: fclean_re all
