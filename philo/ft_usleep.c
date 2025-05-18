#include "philosophers.h"

void	ft_usleep(t_philo *philo)
{
	if (philo->infos->died)
	{
		printf ("%ld: Philosopher %d is eating\n", get_time() - philo->infos->start_time, philo->id);
		usleep(philo->infos->time_to_e * 1000);
		pthread_mutex_lock(&philo->infos->data_lock);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->infos->data_lock);
		philo->num_meals++;
	}
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	if (philo->infos->died)
	{
		printf ("%ld: Philosopher %d is sleeping\n", get_time() - philo->infos->start_time, philo->id);
		usleep(philo->infos->time_to_s * 1000);
	}
	if (philo->infos->died)
	{
		printf ("%ld: Philosopher %d is thinking\n", get_time() - philo->infos->start_time, philo->id);
	}
}
