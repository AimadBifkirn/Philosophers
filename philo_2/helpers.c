/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:23:54 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/23 11:20:22 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutex_destroy(pthread_mutex_t *res, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&res[i]);
		i++;
	}
}

pthread_mutex_t	*forks_init(int n)
{
	int				i;
	pthread_mutex_t	*res;

	i = 0;
	res = malloc(sizeof(pthread_mutex_t) * n);
	if (!res)
		return (NULL);
	while (i < n)
	{
		if (pthread_mutex_init(&res[i], NULL))
		{
			mutex_destroy(res, i);
			free (res);
			return (NULL);
		}
		i++;
	}
	return (res);
}

long	get_time(void)
{
	struct timeval	time;
	long			res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000LL) + (time.tv_usec / 1000);
	return (res);
}

void	free_all(t_infos **glob)
{
	int	i;

	i = 0;
	free((*glob)->philos);
	while (i < (*glob)->n_philos)
	{
		pthread_mutex_destroy(&(*glob)->forks[i]);
		i++;
	}
	free ((*glob)->forks);
	free (*glob);
	*glob = NULL;
}

void	error_malloc(void)
{
	write (2, "malloc failed !\n", 17);
	exit (1);
}
