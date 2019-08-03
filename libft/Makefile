# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/14 15:22:25 by bomanyte          #+#    #+#              #
#    Updated: 2019/04/23 22:32:00 by bomanyte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  libft.a

SRCS =	./ft_lstadd.c	./ft_arrmemdel.c	./ft_strchr.c	./ft_strlen.c	./ft_strsub.c\
./ft_lstdel.c     ./ft_memmove.c	./ft_countw.c	./ft_strmap.c	./ft_strtrim.c\
./ft_lstdelone.c  ./ft_memset.c     ./ft_strclr.c     ./ft_strmapi.c    ./ft_tolower.c\
./ft_atoi.c       ./ft_lstiter.c    ./ft_putchar.c    ./ft_strcmp.c     ./ft_strncat.c    ./ft_toupper.c\
./ft_bzero.c      ./ft_lstmap.c     ./ft_putchar_fd.c ./ft_strcpy.c     ./ft_strncmp.c\
./ft_isalnum.c    ./ft_lstnew.c     ./ft_putendl.c    ./ft_strdel.c     ./ft_strncpy.c\
./ft_isalpha.c    ./ft_memalloc.c   ./ft_putendl_fd.c ./ft_strdup.c     ./ft_strnequ.c\
./ft_isascii.c    ./ft_memccpy.c    ./ft_putnbr.c     ./ft_strequ.c     ./ft_strnew.c\
./ft_isdigit.c    ./ft_memchr.c     ./ft_putnbr_fd.c  ./ft_striter.c    ./ft_strnstr.c\
./ft_isprint.c    ./ft_memcmp.c     ./ft_putstr.c     ./ft_striteri.c   ./ft_strrchr.c\
./ft_getsmol.c    ./ft_memcpy.c     ./ft_putstr_fd.c  ./ft_strjoin.c    ./ft_strsplit.c\
./ft_itoa.c       ./ft_memdel.c     ./ft_strcat.c     ./ft_strlcat.c    ./ft_strstr.c\
./ft_arrlst.c     ./ft_lstsize.c
FILES = $(SRCS:%.c=%.o)

all: $(NAME)
$(NAME): $(FILES)
	gcc -Wall -Wextra -Werror -c -g $(SRCS) -I .
	ar rc $(NAME) $(FILES)
clean:
	rm -f $(FILES)
fclean: clean
	rm -f $(NAME)
re: fclean all
