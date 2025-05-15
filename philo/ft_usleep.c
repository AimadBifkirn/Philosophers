#include "philosophers.h"

void	ft_usleep(t_philo *philo)
{
	if (get_time() - philo->last_meal_time > philo->infos->time_to_d)
	{
		printf ("%ld: Philosopher %d died\n", get_time(), philo->id);
		philo->infos->died = 0;
		return ;
	}
	usleep(philo->infos->time_to_e * 1000);
	printf ("%ld: Philosopher %d is sleeping\n", get_time(), philo->id);
	usleep(philo->infos->time_to_s * 1000);
	printf ("%ld: Philosopher %d is thinking\n", get_time(), philo->id);
}
