# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 11:46:46 by tnaton            #+#    #+#              #
#    Updated: 2022/04/25 17:33:51 by ghanquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c src libft
vpath %.h src libft
vpath %.o src

NAME = minishell

LIBFT = libft/libft.a

SRC = principale.c analysesyntaxique.c no_quote.c liberation.c fais_dedans.c \
	  exec.c split_empty_line.c strjoin_space.c heredoc.c lance_exec.c

source = $(addprefix src/,$(SRC))

CFLAGS = -Wall -Werror -Wextra -Iinc/MinusculeCoquille.h #-g3 -fsanitize=address

CC =	clang

object = $(source:.c=.o)

$(NAME) : $(object) $(LIBFT) 
	$(CC) $(CFLAGS) $(object) $(LIBFT) -o $@ -lreadline

-include libft/Makefile

$(LIBFT) : $(BONUS) $(SRCS) libft/libft.h
	$(MAKE) bonus -C ./libft

$(object) : inc/MinusculeCoquille.h libft/libft.h

debug : $(object)
	$(CC) $(CFLAGS) -g3 -fsanitize=address $(object) $(LIBFT) -o $@ -lreadline

.PHONY: all
all : $(NAME)

.PHONY: clean
clean :
		rm -rf $(object)
		$(MAKE) clean -C ./libft

.PHONY: fclean
fclean :
		rm -rf $(NAME) $(object)
		$(MAKE) fclean -C ./libft

.PHONY: re
re : fclean all

.SECONDARY: $(object)
