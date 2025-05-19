/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:16:50 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/19 14:06:28 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eate(t_philo *philo)
{
	if (!philo->glob->died)
	{
		pthread_mutex_lock(&philo->glob->data_lock);
		philo->num_meals++;
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->glob->data_lock);
		printf ("%ld %d is eating\n", \
		get_time() - philo->glob->start_time, philo->id);
		usleep (philo->glob->time_to_e * 1000);
	}
}

void	take_fork_and_eate(t_philo *philo, \
pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(&philo->glob->data_lock);
	if (!philo->glob->died)
	{
		pthread_mutex_lock(first);
		printf ("%ld %d has taken a fork\n", \
		get_time() - philo->glob->start_time, philo->id);
		if (philo->glob->n_philos == 1)
		{
			pthread_mutex_unlock(first);
			pthread_mutex_unlock(&philo->glob->data_lock);
			free_all(&philo->glob);
			exit (0);
		}
		pthread_mutex_lock(second);
		printf ("%ld %d has taken a fork\n", \
		get_time() - philo->glob->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->glob->data_lock);
	eate(philo);
	if (!philo->glob->died)
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
	}
}

void	sleap_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->glob->data_lock);
	if (!philo->glob->died)
		printf ("%ld %d is sleeping\n", \
		get_time() - philo->glob->start_time, philo->id);
	pthread_mutex_unlock(&philo->glob->data_lock);
	usleep (philo->glob->time_to_s * 1000);
	pthread_mutex_lock(&philo->glob->data_lock);
	if (!philo->glob->died)
		printf ("%ld %d is thinking\n", \
		get_time() - philo->glob->start_time, philo->id);
	pthread_mutex_unlock(&philo->glob->data_lock);
}

void	*philo_routine(void *glob)
{
	t_philo			*philo;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	philo = (t_philo *)glob;
	first = philo->right;
	second = philo->left;
	if (philo->id % 2 == 0)
	{
		usleep(1000);
		first = philo->left;
		second = philo->right;
	}
	while (!philo->glob->died \
	&& (philo->glob->num_times_eat == -1 \
	|| philo->num_meals < philo->glob->num_times_eat))
	{
		take_fork_and_eate(philo, first, second);
		sleap_think(philo);
		usleep (1000);
	}
	return (NULL);
}
