# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emuller <emuller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 11:39:02 by chabrune          #+#    #+#              #
#    Updated: 2023/04/17 14:58:48 by emuller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#######################################################
###### ARGUMENTS

NAME    	=       minishell
CFLAGS  	=       -Wextra -Wall -Werror -g3
CC      	=       gcc
RM      	=       rm -rf
LIBFT		=		"libft/libft.a"
READLINE	=		-lreadline -L /Users/$$USER/.brew/opt/readline/lib
OBJS    	=       $(SRCS:.c=.o)

#######################################################
###### SOURCES

SRCS       	=	main.c \
				get_env.c \
				lst_utils.c \
				lexer/lexer.c \
				parser/parser1.c \
				parser/parser2.c \
				parser/parser3.c \
				parser/parser_utils.c \
				lexer/check_quotes.c \
				builtins/builtins.c \
				builtins/my_cd.c \
				builtins/my_echo.c \
				builtins/my_env_pwd.c \
				builtins/my_export.c \
				builtins/my_unset.c \
				executor/exec.c \
				executor/heredocs.c \
				expander/expander.c \
				expander/expander_utils.c \
				signal.c \


#######################################################
###### RULES

.c.o:
			${CC} ${CFLAGS} -I /Users/$$USER/.brew/opt/readline/include  -c $< -o $(<:.c=.o)

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C libft
			${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${READLINE} -o ${NAME}

debug:		fclean ${OBJS}
			${MAKE} -C libft
			${CC} ${CFLAGS} -fsanitize=address ${OBJS} ${LIBFT} ${READLINE} -o ${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} -C libft clean

fclean:		clean
			${RM} ${NAME}
			${MAKE} -C libft fclean

re:			fclean all

.PHONY:		all clean re fclean