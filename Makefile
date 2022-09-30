NAME			=	philo
HEADERS			=	philo.h
CC				= 	gcc
RM				= 	rm -rf
CFLAGS 			= 	-g -Wall -Wextra -Werror #-pthread #-fsanitize=address

SRCS	=	main.c	\ 

OBJS	= ${SRCS:.c=.o}

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all:	${NAME}

%.o: %.c	$(HEADERS)
			@${CC} -c ${CFLAGS} -o $@ $< 

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re