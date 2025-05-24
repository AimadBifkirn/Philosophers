/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:24:22 by abifkirn          #+#    #+#             */
/*   Updated: 2025/05/24 13:37:04 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_valid_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (j == 0 && args[i][j] == '+')
				;
			else if (!(args[i][j] >= '0' && args[i][j] <= '9') \
			|| (j == 0 && args[i][j] == '-'))
			{
				write (2, "invalid arguement :", 20);
				write (2, args[i], ft_strlen(args[i]));
				write (2, "\n", 1);
				exit (1);
			}
			j++;
		}
		i++;
	}
}
