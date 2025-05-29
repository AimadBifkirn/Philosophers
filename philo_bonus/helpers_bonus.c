/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:02:32 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/29 12:14:19 by abifkirn         ###   ########.fr       */
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

void	wait_proc_exit(t_infos **glob, int count)
{
	int	i;

	i = 0;
	(*glob)->dide->__align = 0;
	while (i < count)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	cleanup_and_exit(*glob, "fork failed !!\n");
	exit (1);
}

void	wait_for_cheldrin(t_infos *glob)
{
	int	i;

	i = 0;
	while (i < glob->n_philos)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

int	check_died(t_infos *glob)
{
	if (glob->dide->__align == 0)
		return (1);
	return (0);
}
