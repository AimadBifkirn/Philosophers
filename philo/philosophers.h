/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:22:22 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/29 09:07:10 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

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
	pthread_mutex_t	*forks;
	pthread_mutex_t	data_lock;
}	t_infos;

typedef struct s_philo
{
	int				id;
	pthread_t		tr;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	long			last_meal_time;
	int				num_meals;
	t_infos			*glob;
}	t_philo;

int				ft_atoi(char *str, t_infos	**res);
void			check_valid_args(char **args);
size_t			ft_strlen(const char *s);
pthread_mutex_t	*forks_init(int n);
t_philo			*init_philo(t_infos *info);
void			init_glob(t_infos **glob, char **argv);
long			get_time(void);
void			join_threads(t_philo *philo);
void			*philo_routine(void *glob);
void			*gard_routine(void *arg);
void			free_all(t_infos **glob);
void			error_malloc(void);
void			mutex_destroy(pthread_mutex_t *res, int count);

#endif