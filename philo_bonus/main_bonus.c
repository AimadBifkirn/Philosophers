/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:58:28 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/29 15:36:09 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*gard_routine(void	*arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->glob->num_times_eat == -1 \
		|| philo->num_meals < philo->glob->num_times_eat)
	{
		sem_wait(philo->glob->data_lock);
		if (get_time() - philo->last_meal_time > philo->glob->time_to_d \
		|| philo->glob->dide->__align == 0)
		{
			if (philo->glob->dide->__align == 1)
			{
				printf ("%ld %d died\n", get_time() \
				- philo->glob->start_time, philo->id);
				philo->glob->dide->__align = 0;
			}
			sem_post(philo->glob->data_lock);
			return (NULL);
		}
		sem_post(philo->glob->data_lock);
		usleep(1000);
	}
	return (NULL);
}

void	take_fork_and_eate(t_philo *philo)
{
	if (check_died(philo->glob))
		return ;
	sem_wait(philo->glob->take);
	sem_wait(philo->glob->forks);
	if (!check_died(philo->glob))
		printf ("%ld %d has taken a fork\n", \
		get_time() - philo->glob->start_time, philo->id);
	handel_one_philo(philo);
	sem_wait(philo->glob->forks);
	if (!check_died(philo->glob))
		printf ("%ld %d has taken a fork\n", \
		get_time() - philo->glob->start_time, philo->id);
	sem_post(philo->glob->take);
	if (check_died(philo->glob))
		return ;
	sem_wait(philo->glob->data_lock);
	philo->num_meals++;
	philo->last_meal_time = get_time();
	if (!check_died(philo->glob))
		printf ("%ld %d is eating\n", \
		get_time() - philo->glob->start_time, philo->id);
	sem_post(philo->glob->data_lock);
	usleep (philo->glob->time_to_e * 1000);
	sem_post(philo->glob->forks);
	sem_post(philo->glob->forks);
}

void	start_philo(t_philo *philo)
{
	pthread_t	gard;

	pthread_create (&gard, NULL, gard_routine, philo);
	while ((philo->glob->num_times_eat == -1 \
		|| philo->num_meals < philo->glob->num_times_eat) \
		&& !check_died(philo->glob))
	{
		take_fork_and_eate(philo);
		sem_wait(philo->glob->data_lock);
		if (!check_died(philo->glob))
			printf ("%ld %d is sleeping\n", \
			get_time() - philo->glob->start_time, philo->id);
		sem_post(philo->glob->data_lock);
		usleep (philo->glob->time_to_s * 1000);
		sem_wait(philo->glob->data_lock);
		if (!check_died(philo->glob))
			printf ("%ld %d is thinking\n", \
			get_time() - philo->glob->start_time, philo->id);
		sem_post(philo->glob->data_lock);
		usleep (1000);
	}
	pthread_join(gard, NULL);
	cleanup_and_exit(philo->glob, "", 0);
}

void	start_proc(t_infos **glob)
{
	t_philo	philo;
	int		i;
	pid_t	pid;

	i = 0;
	(*glob)->start_time = get_time();
	while (i < (*glob)->n_philos)
	{
		philo.id = i + 1;
		philo.glob = *glob;
		philo.num_meals = 0;
		philo.last_meal_time = (*glob)->start_time;
		pid = fork();
		if (pid < 0)
			wait_proc_exit(glob, i);
		if (pid == 0)
		{
			start_philo(&philo);
			exit(0);
		}
		else
			(*glob)->pids[i] = pid;
		i++;
	}
	wait_for_cheldrin(*glob);
}

int	main(int argc, char **argv)
{
	t_infos	*glob;

	glob = NULL;
	if (argc < 5 || argc > 6)
	{
		write (2, "invalid number of arguments\n", 29);
		return (1);
	}
	check_valid_args(argv + 1);
	init_glob(&glob, argv);
	start_proc(&glob);
	cleanup_and_exit(glob, "", 0);
	return (0);
}
