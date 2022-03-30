# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 11:46:46 by tnaton            #+#    #+#              #
#    Updated: 2022/03/30 12:34:00 by ghanquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c src libft
vpath %.h src libft
vpath %.o src

NAME = minishell

LIBFT = libft/libft.a

source = $(addprefix src/,principale.c analysesyntaxique.c no_quote.c)

CFLAGS = -Wall -Werror -Wextra

CC =	clang

object = $(source:.c=.o)

$(NAME) : $(object) $(LIBFT)
	$(CC) $(CFLAGS) $(object) $(LIBFT) -o $@ -lreadline

-include libft/Makefile

$(LIBFT) : $(source) $(BONUS) libft.h
	$(MAKE) bonus -C ./libft

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
