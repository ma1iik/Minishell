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
			free_mem.c \
			free_mem2.c \
			builtins/pwd.c \
			builtins/echo.c \
			builtins/cd.c \
			builtins/export.c \
			builtins/exit.c \
			builtins/unset.c \
			builtins/env.c \
			redirs.c

OBJS	= ${SRCS:.c=.o}

LIBMAC  =""
OS = ${shell uname}
ifeq ($(OS),Darwin)
	LIBMAC += -L/Users/misrailo/.brew/opt/readline/lib
endif

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