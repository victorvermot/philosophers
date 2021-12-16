NAME = philo
SRCS = philo.c philo_utils.c actions.c
OBJS = ${SRCS:.c=.o}
FLGS = -Wall -Wextra -Werror
GCC = gcc

all:		${NAME}

.c.o:
			${GCC} ${FLGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
			${GCC} ${FLGS} -o $@ $^

clean:
			rm -rf ${OBJS}

fclean: 	clean
			rm -rf ${NAME}

re:			fclean all

.PHONY:		all re clean fclean