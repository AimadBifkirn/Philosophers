#include "philosophers.h"

void	ft_usleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos->data_lock);
	if (philo->infos->died)
	{
		printf ("%ld: Philosopher %d is eating\n", get_time() - philo->infos->start_time, philo->id);
		pthread_mutex_unlock(&philo->infos->data_lock);
		usleep(philo->infos->time_to_e * 1000);
		pthread_mutex_lock(&philo->infos->data_lock);
		philo->last_meal_time = get_time();
		philo->num_meals++;
		pthread_mutex_unlock(&philo->infos->data_lock);
	}
	else
		pthread_mutex_unlock(&philo->infos->data_lock);
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
