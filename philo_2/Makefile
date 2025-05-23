NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3

SRC = main.c ft_atoi.c check_valid_args.c ft_strlen.c helpers.c philo_routine.c gard_routine.c init_glob.c

OBJ = ${SRC:.c=.o}

all: ${NAME}

%.o:%.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean: 
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.SECONDARY: ${OBJ}
