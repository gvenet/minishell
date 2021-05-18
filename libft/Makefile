PROJ_DIR := libft/
SRC_DIR	:= src/
OBJ_DIR	:= obj/
BIN_DIR	:= bin/
INC_DIR	:= inc/

NAME	:= $(BIN_DIR)libft.a
SRC		:= $(SRC_DIR)ft_atoi.c\
	$(SRC_DIR)ft_bzero.c\
	$(SRC_DIR)ft_calloc.c\
	$(SRC_DIR)ft_countwords.c\
	$(SRC_DIR)ft_intlen.c\
	$(SRC_DIR)ft_isalnum.c\
	$(SRC_DIR)ft_isalpha.c\
	$(SRC_DIR)ft_isascii.c\
	$(SRC_DIR)ft_isdigit.c\
	$(SRC_DIR)ft_isprint.c\
	$(SRC_DIR)ft_isspace.c\
	$(SRC_DIR)ft_itoa.c\
	$(SRC_DIR)ft_lstadd_back.c\
	$(SRC_DIR)ft_lstadd_front.c\
	$(SRC_DIR)ft_lstclear.c\
	$(SRC_DIR)ft_lstdelone.c\
	$(SRC_DIR)ft_lstiter.c\
	$(SRC_DIR)ft_lstlast.c\
	$(SRC_DIR)ft_lstmap.c\
	$(SRC_DIR)ft_lstnew.c\
	$(SRC_DIR)ft_lstsize.c\
	$(SRC_DIR)ft_memalloc.c\
	$(SRC_DIR)ft_memccpy.c\
	$(SRC_DIR)ft_memchr.c\
	$(SRC_DIR)ft_memcmp.c\
	$(SRC_DIR)ft_memcpy.c\
	$(SRC_DIR)ft_memdel.c\
	$(SRC_DIR)ft_memdel_2d.c\
	$(SRC_DIR)ft_memmove.c\
	$(SRC_DIR)ft_memset.c\
	$(SRC_DIR)ft_putchar_fd.c\
	$(SRC_DIR)ft_putendl_fd.c\
	$(SRC_DIR)ft_putnbr_fd.c\
	$(SRC_DIR)ft_putstr_fd.c\
	$(SRC_DIR)ft_split.c\
	$(SRC_DIR)ft_strchr.c\
	$(SRC_DIR)ft_strdel_2d.c\
	$(SRC_DIR)ft_strdup.c\
	$(SRC_DIR)ft_strjoin.c\
	$(SRC_DIR)ft_strlcat.c\
	$(SRC_DIR)ft_strlcpy.c\
	$(SRC_DIR)ft_strlen.c\
	$(SRC_DIR)ft_strmapi.c\
	$(SRC_DIR)ft_strncmp.c\
	$(SRC_DIR)ft_strncpy.c\
	$(SRC_DIR)ft_strnstr.c\
	$(SRC_DIR)ft_strrchr.c\
	$(SRC_DIR)ft_strtrim.c\
	$(SRC_DIR)ft_substr.c\
	$(SRC_DIR)ft_tolower.c\
	$(SRC_DIR)ft_str_tolower.c\
	$(SRC_DIR)ft_toupper.c\
	$(SRC_DIR)get_next_line.c\
	$(SRC_DIR)get_next_line_utils.c\
	$(SRC_DIR)ft_str_alpha.c\
	$(SRC_DIR)ft_putchar.c



OBJ		:= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
INCLUDE	:= -Iinc
LDFLAGS	:= -Llib

BS = 32

.PHONY: all clean fclean re
.SILENT:

all: $(NAME)

$(NAME): $(OBJ) | $(BIN_DIR)
	ar rcs $(NAME) $(OBJ)
	echo "$(PROJ_DIR)$@ \033[32mlib created\033[0m"
	echo "--------------------------------------------"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)*.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -D BUFFER_SIZE=$(BS)
	echo "$(PROJ_DIR)$@ \033[32mcreated\033[0m"

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@
	echo "$(PROJ_DIR)$@ \033[32mdir created\033[0m"

clean:
	$(RM) -rf $(OBJ_DIR)
	echo "$(PROJ_DIR)$(OBJ_DIR) \033[31mdir deleted\033[0m"

fclean: clean
	$(RM) -rf $(BIN_DIR)
	echo "$(PROJ_DIR)$(BIN_DIR) \033[31mdir deleted\033[0m"

fclean_re:
	$(RM) -rf $(OBJ_DIR)/*
	echo "$(PROJ_DIR)$(OBJ_DIR)*.o \033[31mdeleted\033[0m"
	$(RM) -rf $(BIN_DIR)
	echo "$(PROJ_DIR)$(BIN_DIR) \033[31mdir deleted\033[0m"

re: fclean_re all
