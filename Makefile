# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnaton <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 11:46:46 by tnaton            #+#    #+#              #
#    Updated: 2022/03/23 11:51:32 by tnaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

source = principale.c

object = $(source:.c=.o)

$(NAME) : $(object)
	gcc $(object) -o $@

.PHONY: all
all : $(NAME)

.PHONY: clean
clean :
		rm -rf $(object)

.PHONY: fclean
fclean :
		rm -rf $(NAME) $(object)

.PHONY: re
re : fclean all

.SECONDARY: $(object)
