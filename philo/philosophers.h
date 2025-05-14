#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_infos
{
	int				n_philos;        // number of philosophers
	int				time_to_d;       // time to die
	int				time_to_s;       // time to sleep
	int				time_to_e;       // time to eat
	int				num_times_eat;   // optional argument
	long			start_time;      // when simulation started
	int				died;            // death flag (0 or 1)
	pthread_mutex_t	*forks;          // array of mutexes (one per fork)
	pthread_mutex_t	print_lock;      // to synchronize output
	pthread_mutex_t	data_lock;       // to protect shared flags
}	t_infos;

typedef struct s_philo
{
	int				id;                // philosopher ID (1 to N)
	pthread_t		tr;                // thread handle
	pthread_mutex_t	*left;             // pointer to left fork
	pthread_mutex_t	*right;            // pointer to right fork
	long			last_meal_time;    // last time they ate (ms)
	int				num_meals;         // number of times they ate
	t_infos			*infos;            // shared simulation data
}	t_philo;


int				ft_atoi(char *str);
void			check_valid_args(char **args);
size_t			ft_strlen(const char *s);
pthread_mutex_t	*forks_init(int n);

#endif