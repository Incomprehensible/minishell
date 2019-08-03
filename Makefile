# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/30 00:17:31 by bomanyte          #+#    #+#              #
#    Updated: 2019/07/30 21:28:02 by bomanyte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = krya

SRC = test.c get_next_line.c

INCLUDES = -I /Users/bomanyte/.brew/opt/readline/include

LIB = -L /Users/bomanyte/.brew/opt/readline/lib -lreadline -lncurses -L libft -lft

all: NAME
	
NAME:
	gcc $(INCLUDES) $(LIB) $(SRC) -o $(NAME)

fclean:
	rm $(NAME)
