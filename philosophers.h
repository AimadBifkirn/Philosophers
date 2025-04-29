#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>

typedef struct s_infos
{
	int	n_philos;
	int	time_to_d;
	int	time_to_s;
	int	time_to_e;
	int	num_times_eat;
}	t_infos;

int	ft_atoi(const char *str);

#endif