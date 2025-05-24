/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:03:59 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/24 22:04:12 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <semaphore.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <signal.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <wait.h>

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
	sem_t			*forks;
	sem_t			*data_lock;
	pid_t			*pids;
}	t_infos;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	long			last_meal_time;
	int				num_meals;
	t_infos			*glob;
}	t_philo;

void	check_valid_args(char **args);
void	init_glob(t_infos **glob, char **argv);
void	error_malloc(void);
long	get_time(void);
void	cleanup_and_exit(t_infos *res, const char *msg);
int		ft_atoi(char *str);
size_t	ft_strlen(const char *s);
void	kill_proc_exit(t_infos **glob, int count);
void	wait_for_cheldrin(t_infos *glob);

#endif