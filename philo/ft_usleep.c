#include "philosophers.h"

void	ft_usleep(t_philo *philo)
{
	usleep(philo->infos->time_to_e * 1000);
	printf ("%ld: Philosopher %d is sleeping\n", get_time() - philo->infos->start_time, philo->id);
	usleep(philo->infos->time_to_s * 1000);
	printf ("%ld: Philosopher %d is thinking\n", get_time() - philo->infos->start_time, philo->id);
}
