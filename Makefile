NAME			=	minishell
HEADERS			=	minishell.h
CC				= 	gcc 
RM				= 	rm -rf
CFLAGS 			=  -g -Wall -Wextra -Werror -fcommon -fsanitize=address

SRCS	=	src/main.c	\
			src/utils.c	\
			src/parsing.c \
			src/lexer.c \
			src/free.c \
			src/tokenize.c \
			src/signal.c \
			src/parsing2.c \
			src/dollar.c \
			src/dollar1.c \
			src/dollar2.c \
			src/exec.c \
			src/exec2.c \
			src/exec3.c \
			src/exec4.c \
			src/exec5.c \
			src/fill_cmdl.c \
			src/free_mem.c \
			src/free_mem2.c \
			src/builtins/pwd.c \
			src/builtins/echo.c \
			src/builtins/cd.c \
			src/builtins/export.c \
			src/builtins/exit.c \
			src/builtins/unset.c \
			src/builtins/env.c \
			src/redirs.c

OBJS	= ${SRCS:.c=.o}

LIBMAC  =""
OS = ${shell uname}
ifeq ($(OS),Darwin)
	LIBMAC += -L/Users/misrailo/.brew/opt/readline/lib
endif

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -L/usr/local/lib -I/usr/local/include -lreadline ${LIBMAC} -o ${NAME}

all:	${NAME}

%.o: %.c	$(HEADERS)
			@${CC} -c ${CFLAGS} -o $@ $< 

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re