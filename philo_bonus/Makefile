NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3

SRC = main_bonus.c ft_atoi_bonus.c check_valid_args_bonus.c ft_strlen_bonus.c helpers_bonus.c init_glob_bonus.c

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
