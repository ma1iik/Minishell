NAME			=	minishell
HEADERS			=	minishell.h
CC				= 	gcc 
RM				= 	rm -rf
CFLAGS 			=  -g -Wall -Wextra -Werror -fcommon -fsanitize=address

SRCS	=	main.c	\
			utils.c	\
			parsing.c \
			lexer.c \
			free.c \
			tokenize.c \
			signal.c \
			parsing2.c \
			dollar.c \
			exec.c \
			fill_cmdl.c \
			builtins/pwd.c

OBJS	= ${SRCS:.c=.o}

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -L/usr/local/lib -I/usr/local/include -lreadline -o ${NAME}

all:	${NAME}

%.o: %.c	$(HEADERS)
			@${CC} -c ${CFLAGS} -o $@ $< 

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re