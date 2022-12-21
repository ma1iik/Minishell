NAME			=	minishell
HEADERS			=	minishell.h
CC				= 	gcc 
RM				= 	rm -rf
CFLAGS 			=  -g -Wall -Wextra -Werror -fcommon

SRCS	=	src/main.c	\
			src/builtins/export.c 	src/builtins/export2.c	src/builtins/export3.c\
			src/exec.c				src/exec2.c			src/exec3.c			src/exec4.c			src/exec5.c \
			src/utils.c				src/utils2.c		src/utils3.c		src/utils4.c \
			src/utils5.c			src/utils6.c		src/utils7.c		src/utils8.c \
			src/parsing.c			src/parsing2.c		src/parsing3.c		src/parsing4.c \
			src/lexer.c				src/lexer2.c		src/lexer3.c \
			src/dollar.c			src/dollar2.c		src/dollar3.c \
			src/tokenize.c			src/tokenize2.c \
			src/fill_cmdl.c 		src/fill_cmdl2.c \
			src/free_mem.c			src/free_mem2.c \
			src/redirs.c			src/redirs2.c \
			src/builtins/unset.c 	src/builtins/unset2.c \
			src/builtins/exit.c \
			src/builtins/echo.c \
			src/builtins/env.c \
			src/builtins/pwd.c \
			src/builtins/cd.c 		src/builtins/cd2.c \
			src/signal.c \

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