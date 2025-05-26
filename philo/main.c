/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:09:11 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/25 15:06:15 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philos(t_philo **philo, t_infos *glob)
{
	int	i;

	i = 0;
	while (i < glob->n_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].glob = glob;
		(*philo)[i].num_meals = 0;
		(*philo)[i].left = &glob->forks[i];
		if (i == glob->n_philos - 1)
			(*philo)[i].right = &glob->forks[0];
		else
			(*philo)[i].right = &glob->forks[i + 1];
		i++;
	}
}

void	create_threads(t_infos **glob)
{
	int	i;
	int	num;

	num = (*glob)->n_philos;
	i = 0;
	(*glob)->start_time = get_time();
	while (i < num)
	{
		(*glob)->philos[i].last_meal_time = (*glob)->start_time;
		pthread_create(&(*glob)->philos[i].tr, \
		NULL, philo_routine, &(*glob)->philos[i]);
		i++;
	}
}

void	join_threads(t_philo *philo)
{
	int	i;
	int	num;

	i = 0;
	num = philo->glob->n_philos;
	while (i < num)
	{
		pthread_join(philo[i].tr, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_infos		*glob;
	pthread_t	gard;

	glob = NULL;
	if (argc < 5 || argc > 6)
	{
		write (2, "invalid number of arguments\n", 29);
		return (1);
	}
	check_valid_args(argv + 1);
	init_glob(&glob, argv);
	init_philos(&glob->philos, glob);
	if (glob->n_philos == 1)
	{
		printf ("%d %d has taken a fork\n", 0, 1);
		printf ("%d %d died\n", glob->time_to_d, 1);
		free_all(&glob);
		return (0);
	}
	create_threads(&glob);
	pthread_create(&gard, NULL, gard_routine, glob);
	join_threads(glob->philos);
	pthread_join(gard, NULL);
	free_all(&glob);
	return (0);
}
