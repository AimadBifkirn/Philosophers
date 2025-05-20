/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:09:11 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/20 11:50:04 by abifkirn         ###   ########.fr       */
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

void	init_glob(t_infos **glob, char **argv)
{
	t_infos	*res;

	res = malloc (sizeof(t_infos));
	res->n_philos = ft_atoi(argv[1]);
	if (res->n_philos == 0 || res->n_philos > 200)
	{
		write (2, "invalid philos number !\n", 25);
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
	res->forks = forks_init(res->n_philos);
	pthread_mutex_init(&(res->data_lock), NULL);
	res->philos = malloc (sizeof(t_philo) * res->n_philos);
	*glob = res;
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
	create_threads(&glob);
	pthread_create(&gard, NULL, gard_routine, glob);
	join_threads(glob->philos);
	pthread_join(gard, NULL);
	free_all(&glob);
	return (0);
}
