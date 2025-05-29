/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:14:34 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/29 08:28:10 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_helper(t_infos **res)
{
	(*res)->forks = forks_init((*res)->n_philos);
	if (!(*res)->forks)
	{
		free ((*res));
		write (2, "mutex_init failed !\n", 21);
		exit (1);
	}
	(*res)->philos = malloc (sizeof(t_philo) * (*res)->n_philos);
	if (!(*res)->philos)
	{
		mutex_destroy ((*res)->forks, (*res)->n_philos);
		free ((*res)->forks);
		free ((*res));
		error_malloc();
	}
	if (pthread_mutex_init(&((*res)->data_lock), NULL))
	{
		free ((*res)->philos);
		mutex_destroy ((*res)->forks, (*res)->n_philos);
		free ((*res)->forks);
		free ((*res));
		write (2, "mutex_init failed !\n", 21);
		exit (1);
	}
}

void	init_glob(t_infos **glob, char **argv)
{
	t_infos	*res;

	res = malloc (sizeof(t_infos));
	if (!res)
		error_malloc();
	res->n_philos = ft_atoi(argv[1]);
	if (res->n_philos == 0 || res->n_philos > 200)
	{
		write (2, "invalid philos number !\n", 25);
		free (res);
		exit (1);
	}
	res->time_to_d = ft_atoi(argv[2]);
	res->time_to_e = ft_atoi(argv[3]);
	res->time_to_s = ft_atoi(argv[4]);
	if (argv[5])
		res->num_times_eat = ft_atoi(argv[5]);
	else
		res->num_times_eat = -1;
	res->died = 0;
	init_helper(&res);
	*glob = res;
}
