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
	while (c_philo->infos->died && (c_philo->infos->num_times_eat == -1 || c_philo->num_meals < c_philo->infos->num_times_eat))
	{
		if (c_philo->id % 2 == 1)
		{
			usleep(1000);
			pthread_mutex_lock(c_philo->left);
			if (!c_philo->infos->died)
			{
				pthread_mutex_unlock(c_philo->left);
				return (NULL);
			}
			printf ("%ld: Philosopher %d toke a fork\n", get_time() - c_philo->infos->start_time, c_philo->id);
			pthread_mutex_lock(c_philo->right);
			if (!c_philo->infos->died)
			{
				pthread_mutex_unlock(c_philo->right);
				return (NULL);
			}
			printf ("%ld: Philosopher %d toke a fork\n", get_time() - c_philo->infos->start_time, c_philo->id);
		}
		else
		{
			pthread_mutex_lock(c_philo->right);
			if (!c_philo->infos->died)
			{
				pthread_mutex_unlock(c_philo->right);
				return (NULL);
			}
			printf ("%ld: Philosopher %d toke a fork\n", get_time() - c_philo->infos->start_time, c_philo->id);
			pthread_mutex_lock(c_philo->left);
			if (!c_philo->infos->died)
			{
				pthread_mutex_lock(c_philo->left);
				return (NULL);
			}
			printf ("%ld: Philosopher %d toke a fork\n", get_time() - c_philo->infos->start_time, c_philo->id);
		}
		ft_usleep(philo);
		usleep(1000);
	}
	return (philo);
}

void	*monitore_routine(void *philo)
{
	int	i;
	t_philo	*c_philo;
	
	c_philo = (t_philo *)philo;
	while (c_philo->infos->died)
	{
		i = 0;
		while (i < c_philo->infos->n_philos)
		{
			pthread_mutex_lock(&c_philo[i].infos->data_lock);
			if (c_philo[i].infos->num_times_eat != -1 && c_philo[i].num_meals == c_philo->infos->num_times_eat)
			{
				i++;
				continue ;
			}
			if ((get_time() - c_philo[i].last_meal_time) > c_philo[i].infos->time_to_d)
			{
				printf ("%ld: Philosopher %d died\n", get_time() - c_philo[i].infos->start_time, c_philo[i].id);
				c_philo[i].infos->died = 0;
				pthread_mutex_unlock(&c_philo[i].infos->data_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&c_philo[i].infos->data_lock);
			i++;
		}
	}
	return (NULL);
}

t_philo	*init_philo(t_infos *info)
{
	int	i;
	t_philo	*philo;
	long	t;

	philo = malloc (sizeof(t_philo) * info->n_philos);
	i = 0;
	t = get_time();
	while (i < info->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].infos = info;
		philo[i].num_meals = 0;
		philo[i].left = &info->forks[i];
		philo[i].right = &info->forks[(i + 1) % info->n_philos];
		philo[i].last_meal_time = t;
		i++;
	}
	return (philo);
}

long	get_time()
{
	struct	timeval time;
	long	res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000LL) + (time.tv_usec / 1000);
	return (res);
}
