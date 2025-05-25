/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_glob_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:14:34 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/25 09:14:38 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup_and_exit(t_infos *res, const char *msg)
{
	if (res->pids)
		free(res->pids);
	if (res->forks != SEM_FAILED)
	{
		sem_close(res->forks);
		sem_unlink("/sem_forks");
	}
	if (res->data_lock != SEM_FAILED)
	{
		sem_close(res->data_lock);
		sem_unlink("/sem_data");
	}
	free(res);
	write(2, msg, ft_strlen(msg));
	exit(0);
}

void	null_initial(t_infos **res)
{
	(*res)->data_lock = NULL;
	(*res)->forks = NULL;
	(*res)->pids = NULL;
}

void	init_helper(t_infos **res, char **argv)
{
	(*res)->time_to_d = ft_atoi(argv[2]);
	(*res)->time_to_e = ft_atoi(argv[3]);
	(*res)->time_to_s = ft_atoi(argv[4]);
	if (argv[5])
		(*res)->num_times_eat = ft_atoi(argv[5]);
	else
		(*res)->num_times_eat = -1;
}

void	init_glob(t_infos **glob, char **argv)
{
	t_infos	*res;

	sem_unlink("/sem_forks");
	sem_unlink("/sem_data");
	res = malloc (sizeof(t_infos));
	if (!res)
		error_malloc();
	null_initial(&res);
	res->n_philos = ft_atoi(argv[1]);
	if (res->n_philos == 0 || res->n_philos > 200)
		cleanup_and_exit(res, "invalid philos number !\n");
	init_helper(&res, argv);
	res->pids = malloc(sizeof(pid_t) * res->n_philos);
	if (!res->pids)
		cleanup_and_exit(res, "failed to allocate pids !!\n");
	res->forks = sem_open("/sem_forks", O_CREAT, 0644, res->n_philos);
	if (res->forks == SEM_FAILED)
		cleanup_and_exit(res, "sem_open(forks) failed !!\n");
	res->data_lock = sem_open("/sem_data", O_CREAT, 0644, 1);
	if (res->data_lock == SEM_FAILED)
		cleanup_and_exit(res, "sem_open(data_lock) failed !!\n");
	*glob = res;
}
