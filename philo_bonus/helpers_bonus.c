/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:02:32 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/24 22:02:33 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	time;
	long			res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000LL) + (time.tv_usec / 1000);
	return (res);
}

void	error_malloc(void)
{
	write (2, "malloc failed !\n", 17);
	exit (1);
}

void	kill_proc_exit(t_infos **glob, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		kill ((*glob)->pids[i], SIGTERM);
		i++;
	}
	cleanup_and_exit(*glob, "fork failed !!\n");
	exit (1);
}

void	wait_for_cheldrin(t_infos *glob)
{
	int	status;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < glob->n_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			while (j < glob->n_philos)
			{
				kill(glob->pids[j], SIGTERM);
				j++;
			}
			break ;
		}
		i++;
	}
}
