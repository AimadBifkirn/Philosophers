/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gard_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:12:45 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/23 11:07:51 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_num_meals(t_infos *g)
{
	pthread_mutex_lock(&g->data_lock);
	if (g->philos[0].num_meals != 1 \
	&& g->philos[0].num_meals == g->num_times_eat)
	{
		pthread_mutex_unlock(&g->data_lock);
		return (1);
	}
	pthread_mutex_unlock(&g->data_lock);
	return (0);
}

void	*gard_routine(void *arg)
{
	t_infos	*g;
	int		i;

	g = (t_infos *)arg;
	while (!g->died)
	{
		i = -1;
		if (check_num_meals(g))
			return (NULL);
		while (++i < g->n_philos)
		{
			pthread_mutex_lock(&g->data_lock);
			if (get_time() - g->philos[i].last_meal_time > g->time_to_d)
			{
				printf("%ld %d died\n", get_time() \
				- g->start_time, g->philos[i].id);
				g->died = 1;
				pthread_mutex_unlock(&g->data_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&g->data_lock);
		}
	}
	return (NULL);
}
