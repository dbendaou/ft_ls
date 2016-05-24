# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/10 16:16:05 by dbendaou          #+#    #+#              #
#    Updated: 2016/05/23 18:42:05 by dbendaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	ft_ls

SRC_PATH	=	srcs
SRC_NAME	= 	append.c \
				arg_reader.c \
				check.c \
				error.c \
				free.c \
				ft_ls.c \
				get_devsize.c \
				get_max.c \
				get_pn.c \
				list.c \
				lprint.c \
				lprint_gu.c \
				lprint_oth.c \
				openlink.c \
				print_rgt.c \
				printer.c \
				recursive.c \
				reverse.c \
				time_append.c \


OBJ_NAME	=	$(SRC_NAME:.c=.o)
OBJ_PATH	=	objs

CPPFLAGS	= 	-Iinclude
CFLAGS 		=	-Wall -Wextra -Werror
LDFLAGS		=	-Llibft
LDLIBS		=	-lft

CC			=	clang

SRC			=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ 		=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

#COLORS
C_GOOD	=	"\033[32mSUCCESS\033[0m"
C_ORAN	=	"\033[33mCleaning "
C_RED	=	"\033[31mDelete   "
C_WHIT	= 	"\033[0m [ $(NAME) ]"
C_BLUE	=	"\033[34;1mCompiling"

all 	:	$(NAME)

$(NAME)	:	$(OBJ) libft/libft.a
		@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
		@echo $(C_BLUE) $(C_WHIT) $(C_GOOD)

libft/libft.a :
		@make -C libft

objs/%.o: 	srcs/%.c
		@mkdir $(OBJ_PATH) 2> /dev/null || true
		@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean :
		@rm -f $(OBJ)
		@rmdir $(OBJ_PATH) 2> /dev/null || true
		@echo $(C_ORAN) $(C_WHIT) $(C_GOOD)

fclean :	 clean
		@rm -rf $(NAME)
		@echo $(C_RED) $(C_WHIT) $(C_GOOD)

re :		fclean all

.PHONY: 	all, clean, fclean, re