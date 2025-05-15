#include "philosophers.h"

pthread_mutex_t	*forks_init(int n)
{
	int				i;
	pthread_mutex_t	*res;

	i = 0;
	res = malloc(sizeof(pthread_mutex_t) * n);
	while (i < n)
	{
		pthread_mutex_init(&res[i], NULL);
		i++;
	}
	return(res);
}

void	*routine_of_philo(void *philo)
{
	t_philo	*c_philo;

	c_philo = philo;
	while (c_philo->infos->died && c_philo->num_meals != 0)
	{
		if (c_philo->id % 2 == 1)
		{
			pthread_mutex_lock(c_philo->left);
			pthread_mutex_lock(c_philo->right);
		}
		else
		{
			usleep(1000); // delay to avoid two philos locking the same fork at the same time.
			pthread_mutex_lock(c_philo->right);
			pthread_mutex_lock(c_philo->left);
		}
		printf ("%ld: Philosopher %d is eating\n", get_time(), c_philo->id);
		if (c_philo->num_meals != -1)
			c_philo->num_meals--;
		c_philo->last_meal_time = get_time();
		ft_usleep(philo);
		pthread_mutex_unlock(c_philo->left);
		pthread_mutex_unlock(c_philo->right);
	}
	return (philo);
}

void	*monitore_routine(t_philo **philo)
{
	
}

t_philo	*init_philo(t_infos *info)
{
	int	i;
	t_philo	*philo;

	philo = malloc (sizeof(t_philo) * info->n_philos + 1);
	i = 0;
	while (i < info->n_philos)
	{
		pthread_create(&philo[i].tr, NULL, routine_of_philo, &philo[i]);
		philo[i].id = i + 1;
		philo[i].infos = info;
		philo[i].num_meals = 0;
		philo[i].left = &info->forks[i];
		philo[i].right = &info->forks[(i + 1) % info->n_philos];
		philo[i].last_meal_time = info->start_time;
		i++;
	}
	pthread_create(&philo[info->n_philos], NULL, monitore_routine, &philo);
	return (philo);
}

long	get_time()
{
	struct	timeval time;
	long	res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (res);
}
