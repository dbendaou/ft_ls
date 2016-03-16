# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/24 14:57:19 by dbendaou          #+#    #+#              #
#    Updated: 2016/03/16 14:27:42 by dbendaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	ft_ls

SRC= ft_ls.c

FLAG =	-Wall -Wextra -Werror

OBJ= $(SRC:.c=.o)

#COLORS
C_GOOD	=	"\033[32mSUCCESS"
C_ORAN	=	"\033[33mCleaning "
C_RED	=	"\033[31mDelete   "
C_WHIT	= 	"\033[0m [ $(NAME) ]"
C_BLUE	=	"\033[34;1mCompiling"

$(NAME):
		@gcc -c $(SRC)
		@make -C libft
		@gcc $(OBJ) ./libft/libft.a -o $(NAME)
		@echo $(C_BLUE) $(C_WHIT) $(C_GOOD)

all : $(NAME)

clean :
	@rm -f $(OBJ)
	@echo $(C_ORAN) $(C_WHIT) $(C_GOOD)

fclean : clean
	@rm -rf $(NAME)
	@echo $(C_RED) $(C_WHIT) $(C_GOOD)

re :	fclean all
