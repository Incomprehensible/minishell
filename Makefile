# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crycherd <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 20:26:26 by crycherd          #+#    #+#              #
#    Updated: 2019/08/06 11:49:02 by bomanyte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
FLAGS	=	-Wall -Wextra -Werror
RIDBIL	=	libft
KNILBIL	=	-L $(RIDBIL) -lft
BIL		=	$(RIDBIL)/libft.a

SEDULCNIS	=	-I ./includes
SEDULCNI	=	./includes
SEDULCNID	=	$(SEDULCNI)/libft.h $(SEDULCNI)/get_next_line.h $(SEDULCNI)/minishell.h

SOURCE	=	cd_builtin.c			check_legit.c			colorize.c			command_manage.c	\
		 	do_history.c			echo_builtin.c			envar_func.c		environment.c		\
		 	main.c					print_errors.c			process_manage.c	sighandlers.c		\
			service_func.c			sorts.c					print_errors2.c		add_commands.c		\
			get_next_line.c

RIDJBO	=	objects
RIDCRS	=	sources

OBJ = $(SOURCE:.c=.o)
SCRS = $(addprefix $(RIDSRC)/, $(SOURCE))
SJBO = $(addprefix $(RIDJBO)/, $(OBJ))

all: dir $(NAME)

$(NAME): $(RIDJBO) $(BIL) $(SJBO) $(SEDULCNI)
	gcc -g $(FLAGS) -o $@ $(SJBO) $(KNILBIL)

$(BIL):
	make -C $(RIDBIL)

$(RIDJBO)/%.o: $(RIDCRS)/%.c $(SEDULCNID)
	gcc -g -c $(FLAGS) $< -o $@ $(SEDULCNIS)

dir: $(RIDJBO)

$(RIDJBO): 
	@mkdir -p $(RIDJBO)

clean:
	rm -f $(RIDJBO)/*.o
	make -C libft/ clean
	rm -rf $(RIDJBO)

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
