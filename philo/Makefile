SRCS = ${addprefix srcs/, philo.c philo_utils.c init.c threads.c}
NAME = philo
OBJS = ${SRCS:.c=.o}
FLGS = -Wall -Wextra -Werror
GCC = gcc -g -O0
CLR_GREEN = \033[0;32m
CLR_RESET = \033[0m

all:		${NAME}

.c.o:
			${GCC} ${FLGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
			@echo "${CLR_GREEN}Objects created${CLR_RESET}"
			${GCC} ${FLGS} -o $@ $^
			@echo "${CLR_GREEN}Exe created${CLR_RESET}"

clean:
			rm -rf ${OBJS}

fclean: 	clean
			rm -rf ${NAME}

re:			fclean all

.PHONY:		all re clean fclean