# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hivian <hivian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/01 10:58:54 by hivian            #+#    #+#              #
#    Updated: 2017/01/13 11:33:33 by hivian           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 		= ft_nm
NAME2 		= ft_otool
CC 	 		= clang
CFLAGS 		= -Wall -Wextra -Werror

LIBS		= -L libft/ -lft -lm

SRC_DIR1 	= nm/srcs
INC_DIR1 	= nm/incs

SRC_DIR2 	= otool/srcs
INC_DIR2 	= otool/incs

SRC1  		= $(SRC_DIR1)/main.c \
			  $(SRC_DIR1)/nm.c \
			  $(SRC_DIR1)/error.c \
			  $(SRC_DIR1)/arch64.c \
			  $(SRC_DIR1)/arch32.c \
			  $(SRC_DIR1)/print.c \
			  $(SRC_DIR1)/sort.c \
			  $(SRC_DIR1)/util.c \

SRC2  		= $(SRC_DIR2)/main.c \
			  $(SRC_DIR2)/otool.c \
			  $(SRC_DIR2)/error.c \
			  $(SRC_DIR2)/arch64.c \
			  $(SRC_DIR2)/arch32.c \
			  $(SRC_DIR2)/print.c \

OBJ1  		= $(SRC1:%.c=%.o)
OBJ2  		= $(SRC2:%.c=%.o)
LIBFT 		= libft/libft.a

all: $(NAME1) $(NAME2)

$(LIBFT):
	@printf "Compiling libft ... "
	@make -C libft/
	@echo "Done"

$(NAME1): $(LIBFT) $(OBJ1)
	@printf "Compiling ft_nm ..."
	@$(CC) $(CFLAGS) -o $(NAME1) $(OBJ1) $(LIBS)
	@echo "Done"

$(NAME2): $(LIBFT) $(OBJ2)
	@printf "Compiling ft_otool ..."
	@$(CC) $(CFLAGS) -o $(NAME2) $(OBJ2) $(LIBS)
	@echo "Done"

%.o: %.c
	@$(CC) $(CFLAGS) -I $(INC_DIR1) -I $(INC_DIR2) -o $@ -c $<

clean:
	@rm -rf $(OBJ1)
	@rm -rf $(OBJ2)
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME1)
	@rm -f $(NAME2)
	@make fclean -C libft/

re: fclean all

norm :
	@make -C libft/ norm
	@norminette $(SRC_DIR1) $(INC_DIR1) $(SRC_DIR2) $(INC_DIR2)

.PHONY: all clean fclean re
