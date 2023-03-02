# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 11:39:02 by chabrune          #+#    #+#              #
#    Updated: 2023/03/02 10:16:25 by chabrune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#######################################################
###### ARGUMENTS

NAME    	=       minishell
CFLAGS  	=       -Wextra -Wall -Werror -g3
CC      	=       gcc
RM      	=       rm -rf
LIBFT		=		"/Users/chabrune/Desktop/42-school/libft/libft.a"
READLINE	=		 -lreadline -L "/Users/chabrune/.brew/opt/readline/lib"
OBJS    	=       $(SRCS:.c=.o)

#######################################################
###### SOURCES

SRCS       	=	main.c \


#######################################################
###### RULES

.c.o:
			gcc ${CFLAGS} -I /Users/chabrune/.brew/opt/readline/include  -c $< -o $(<:.c=.o)

all:		${NAME}

${NAME}:	${OBJS}
			${MAKE} -C /Users/chabrune/Desktop/42-school/libft
			gcc ${CFLAGS} ${LIBFT} ${OBJS} ${READLINE} -o ${NAME}

debug:		fclean ${OBJS}
			${MAKE} -C /Users/chabrune/Desktop/42-school/libft
			gcc ${CFLAGS} -fsanitize=address ${LIBFT} ${OBJS} ${READLINE} -o ${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} -C /Users/chabrune/Desktop/42-school/libft clean

fclean:		clean
			${RM} ${NAME}
			${MAKE} -C /Users/chabrune/Desktop/42-school/libft fclean

re:			fclean all

.PHONY:		all clean re fclean