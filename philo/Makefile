NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread

SRC = main.c ft_atoi.c check_valid_args.c ft_strlen.c ft_usleep.c helpers.c

OBJ = ${SRC:.c=.o}

all: ${NAME}

%.o:%.c
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJ}
	${CC} -g ${OBJ} -o ${NAME} -lreadline

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.SECONDARY:
