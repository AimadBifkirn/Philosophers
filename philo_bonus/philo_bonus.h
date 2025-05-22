#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
#include <semaphore.h>

struct	s_philo;

typedef struct s_infos
{
	int				n_philos;
	int				time_to_d;
	int				time_to_s;
	int				time_to_e;
	int				num_times_eat;
	long			start_time;
	int				died;
	struct s_philo	*philos;
	sem_t	*forks;
	sem_t	data_lock;
}	t_infos;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	int				num_meals;
	t_infos			*glob;
}	t_philo;

void	check_valid_args(char **args);

#endif