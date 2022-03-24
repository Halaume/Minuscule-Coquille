# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 11:46:46 by tnaton            #+#    #+#              #
#    Updated: 2022/03/24 12:05:11 by tnaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c src libft
vpath %.h src libft
vpath %.o src

NAME = minishell

LIBFT = libft/libft.a

source = src/principale.c src/analysesyntaxique.c

CFLAGS = -Wall -Werror -Wextra

object = $(source:.c=.o)

$(NAME) : $(object) $(LIBFT)
	gcc $(CFLAGS) $(object) $(LIBFT) -o $@ -lreadline

-include libft/Makefile

$(LIBFT) : $(source) $(BONUS) libft.h
	$(MAKE) bonus -C ./libft

debug : 
	gcc $(CFLAGS) -g3 -fsanitize=address $(object) $(LIBFT) -o $@ -lreadline

.PHONY: all
all : $(NAME)

.PHONY: clean
clean :
		rm -rf $(object)
		$(MAKE) clean -C ./libft

.PHONY: fclean
fclean :
		rm -rf $(NAME) $(object)

.PHONY: re
re : fclean all

.SECONDARY: $(object)
