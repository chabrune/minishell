# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 11:39:02 by chabrune          #+#    #+#              #
#    Updated: 2023/05/14 16:22:49 by chabrune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#######################################################
###### ARGUMENTS

NAME    		=       minishell
CFLAGS  		=       -Wextra -Wall -Werror -g3
CC      		=       gcc
RM      		=       rm -rf
LIBFT			=		"libft/libft.a"
OBJS    		=       $(SRCS:.c=.o)
READLINE_DIR 	= 		$(shell brew --prefix readline)
READLINE_LIB 	= 		-lreadline -lhistory -L $(READLINE_DIR)/lib
INCLUDES 		=		-Iincludes -I$(LIBFT) -I$(READLINE_DIR)/include

#######################################################
###### SOURCES

SRCS       	=	main.c \
				get_env.c \
				lst_utils.c \
				lst_utils2.c \
				lexer/lexer.c \
				lexer/lexer2.c \
				parser/parser1.c \
				parser/parser2.c \
				parser/parser3.c \
				parser/parser_utils.c \
				builtins/builtins.c \
				builtins/builtins2.c \
				builtins/my_cd.c \
				builtins/my_echo.c \
				builtins/my_env_pwd.c \
				builtins/my_export.c \
				builtins/my_unset.c \
				executor/exec.c \
				executor/exec2.c \
				executor/heredocs.c \
				executor/redir.c \
				expander/expander.c \
				expander/expander2.c \
				expander/expander3.c \
				expander/expander_utils.c \
				signal.c \
				error.c \
				executor/exec3.c \
				lexer/lexer3.c \
				builtins/my_export2.c \
				builtins/my_export3.c \
				builtins/my_export4.c \
				builtins/my_cd2.c \
				expander/expander4.c \

#######################################################
###### RULES

.c.o:
			${CC} ${CFLAGS} $(INCLUDES) -c $< -o $(<:.c=.o)

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C libft
			${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${READLINE_LIB} -o ${NAME}

debug:		fclean ${OBJS}
			${MAKE} -C libft
			${CC} ${CFLAGS} -fsanitize=address ${OBJS} ${LIBFT} ${READLINE_LIB} -o ${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} -C libft clean

fclean:		clean
			${RM} ${NAME}
			${MAKE} -C libft fclean

re:			fclean all

.PHONY:		all clean re fclean
