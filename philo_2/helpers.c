/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:23:54 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/20 13:53:59 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*forks_init(int n)
{
	int				i;
	pthread_mutex_t	*res;

	i = 0;
	res = malloc(sizeof(pthread_mutex_t) * n);
	while (i < n)
	{
		pthread_mutex_init(&res[i], NULL);
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
