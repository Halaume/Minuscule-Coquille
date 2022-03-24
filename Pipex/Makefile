# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 13:44:31 by ghanquer          #+#    #+#              #
#    Updated: 2022/03/22 11:34:57 by ghanquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BNS_NAME = pipex_bonus

INC_DIR =		inc
OBJ_DIR = 		obj
SRC_DIR	= 		src

SRC =			$(SRC_FT:%=$(SRC_DIR)/%.c)

OBJ =			$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ_DIRS =		$(OBJ_DIR)

BNS_INC_DIR =		inc
BNS_OBJ_DIR = 		obj_bonus
BNS_SRC_DIR	= 		src_bonus

BNS_SRC =			$(BNS_SRC_FT:%=$(BNS_SRC_DIR)/%.c)

BNS_OBJ =			$(BNS_SRC:$(BNS_SRC_DIR)%.c=$(BNS_OBJ_DIR)%.o)

BNS_OBJ_DIRS =		$(BNS_OBJ_DIR)

CC = clang $(CFLAGS)

RM = rm -fr

CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

.c.o:
	$(CC) -c $< -o $(<:.c=.o)

#HOW TO LIST .c 
#	ls -l | awk '{print $9}' | grep -E ".c$"| sed "s/\.c/ \\\/g" | sed '$s/\\$//g'

SRC_FT =	ft_strncmp \
			main \
			ft_split \
			ft_join \
			ft_strlcpy \
			pipex 

BNS_SRC_FT =	child_bonus \
				free_fun_bonus \
				ft_join_bonus \
				ft_split_bonus \
				ft_strlcpy_bonus \
				ft_strncmp_bonus \
				get_next_line \
				get_next_line_utils \
				here_doc_bonus \
				main_bonus \
				pipex_bonus \
				recur

all: $(NAME) inc/pipex.h

$(OBJ_DIRS): inc/pipex.h
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/pipex.h
	$(CC) -c $< -o $@

$(NAME): $(OBJ_DIRS) $(SRC) inc/pipex.h
	$(MAKE) -j $(OBJ)
	$(CC) $(OBJ) -o $@

bonus: $(BNS_NAME) inc/pipex_bonus.h

$(BNS_OBJ_DIRS): inc/pipex_bonus.h
	mkdir -p $@

$(BNS_OBJ_DIR)/%.o: $(BNS_SRC_DIR)/%.c inc/pipex_bonus.h
	$(CC) -c $< -o $@

$(BNS_NAME): $(BNS_OBJ_DIRS) $(BNS_SRC) inc/pipex_bonus.h
	$(MAKE) -j $(BNS_OBJ)
	$(CC) $(BNS_OBJ) -o $@

clean_bonus :
	$(RM) $(BNS_OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean clean_bonus
	$(RM) $(NAME)
	$(RM) $(BNS_NAME)

re: fclean all

define print_aligned_coffee
    @t=$(NAME); \
	l=$${#t};\
	i=$$((8 - l / 2));\
	echo "             \0033[1;32m\033[3C\033[$${i}CAnd Your program \"$(NAME)\" "
endef

coffee: all clean
	@echo ""
	@echo "                                {"
	@echo "                             {   }"
	@echo "                              }\0033[1;34m_\0033[1;37m{ \0033[1;34m__\0033[1;37m{"
	@echo "                           \0033[1;34m.-\0033[1;37m{   }   }\0033[1;34m-."
	@echo "                          \0033[1;34m(   \0033[1;37m}     {   \0033[1;34m)"
	@echo "                          \0033[1;34m| -.._____..- |"
	@echo "                          |             ;--."
	@echo "                          |            (__  \ "
	@echo "                          |             | )  )"
	@echo "                          |   \0033[1;96mCOFFEE \0033[1;34m   |/  / "
	@echo "                          |             /  / "
	@echo "                          |            (  / "
	@echo "                          \             | "
	@echo "                            -.._____..- "
	@echo ""
	@echo ""
	@echo "\0033[1;32m\033[3C                    Take Your Coffee"
	$(call print_aligned_coffee)

.SECONDARY: $(OBJ) $(OBJ_DIR) $(BNS_OBJ) $(BNS_OBJ_DIR)
.PHONY: all bonus clean fclean re coffee clean_bonus
