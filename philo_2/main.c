#include "philosophers.h"

void	free_all(t_infos **glob)
{
	int	i;

	i = 0;
	free((*glob)->philos);
	while (i < (*glob)->n_philos)
	{
		pthread_mutex_destroy(&(*glob)->forks[i]);
		i++;
	}
	free ((*glob)->forks);
	free (*glob);
	*glob = NULL;
}

void	init_philos(t_philo **philo, t_infos *glob)
{
	int	i;

	i = 0;
	while (i < glob->n_philos)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].glob = glob;
		(*philo)[i].num_meals = 0;
		(*philo)[i].left = &glob->forks[i];
		if (i == glob->n_philos - 1)
			(*philo)[i].right = &glob->forks[0];
		else
		(*philo)[i].right = &glob->forks[i + 1];
		i++;
	}
	
}

void	init_glob(t_infos **glob, char **argv)
{
	t_infos	*res;

	res = malloc (sizeof(t_infos));
	res->n_philos = ft_atoi(argv[1]);
	if (res->n_philos == 0 || res->n_philos > 200)
	{
		write (2, "invalid philos number !\n", 25);
		exit (1);
	}
	res->time_to_d = ft_atoi(argv[2]);
	res->time_to_e = ft_atoi(argv[3]);
	res->time_to_s = ft_atoi(argv[4]);
	if (argv[5])
		res->num_times_eat = ft_atoi(argv[5]);
	else
		res->num_times_eat = -1;
	res->died = 0;
	res->forks = forks_init(res->n_philos);
	pthread_mutex_init(&(res->data_lock), NULL);
	res->philos = malloc (sizeof(t_philo) * res->n_philos);
	*glob = res;
}

void	eate(t_philo *philo)
{
	if (!philo->glob->died)
	{
		pthread_mutex_lock(&philo->glob->data_lock);
		philo->num_meals++;
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->glob->data_lock);
		printf ("%ld %d is eating\n", get_time() - philo->glob->start_time, philo->id);
		usleep (philo->glob->time_to_e * 1000);
	}
}

void	take_fork_and_eate(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(&philo->glob->data_lock);
	if (!philo->glob->died)
	{
		pthread_mutex_lock(first);
		printf ("%ld %d has taken a fork\n", get_time() - philo->glob->start_time, philo->id);
		if (philo->glob->n_philos == 1)
		{
			pthread_mutex_unlock(first);
			free_all(&philo->glob);
			exit (0);
		}
		pthread_mutex_lock(second);
		printf ("%ld %d has taken a fork\n", get_time() - philo->glob->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->glob->data_lock);
	eate(philo);
}

void	sleap_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->glob->data_lock);
	if (!philo->glob->died)
		printf ("%ld %d is sleeping\n", get_time() - philo->glob->start_time, philo->id);
	pthread_mutex_unlock(&philo->glob->data_lock);
	usleep (philo->glob->time_to_s * 1000);
	pthread_mutex_lock(&philo->glob->data_lock);
	if (!philo->glob->died)
		printf ("%ld %d is thinking\n", get_time() - philo->glob->start_time, philo->id);
	pthread_mutex_unlock(&philo->glob->data_lock);
}

void	*philo_routine(void *glob)
{
	t_philo	*philo;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	philo = (t_philo *)glob;
	first = philo->right;
	second = philo->left;
	if (philo->id % 2 == 0)
	{
		usleep(1000);
		first = philo->left;
		second = philo->right;
	}
	while (!philo->glob->died && (philo->glob->num_times_eat == -1  ||  philo->num_meals < philo->glob->num_times_eat))
	{
		take_fork_and_eate(philo, first, second);
		if (!philo->glob->died)
		{
			pthread_mutex_unlock(first);
			pthread_mutex_unlock(second);
		}
		sleap_think(philo);
		usleep (1000);
	}
	return (NULL);
}

void	create_threads(t_infos **glob)
{
	int	i;
	int	num;

	num = (*glob)->n_philos;
	i = 0;
	(*glob)->start_time = get_time();
	while (i < num)
	{
		(*glob)->philos[i].last_meal_time = (*glob)->start_time;
		pthread_create(&(*glob)->philos[i].tr, NULL, philo_routine, &(*glob)->philos[i]);
		i++;
	}
}

void *gard_routine(void *arg)
{
    t_infos *g;
    int i;

	g = (t_infos *)arg;
    while (!g->died)
    {
		i = 0;
		if (g->philos[i].num_meals != 1 && g->philos[i].num_meals == g->num_times_eat)
			return (NULL);
        while (i < g->n_philos)
        {
			pthread_mutex_lock(&g->data_lock);
            if (get_time() - g->philos[i].last_meal_time > g->time_to_d)
            {
                printf("%ld %d died\n", get_time() - g->start_time, g->philos[i].id);
                g->died = 1;
                pthread_mutex_unlock(&g->data_lock);
                return NULL;
            }
			pthread_mutex_unlock(&g->data_lock);
			i++;
        }
    }
    return NULL;
}

void	join_threads(t_philo *philo)
{
	int	i;
	int	num;

	i = 0;
	num = philo->glob->n_philos;
	while (i < num)
	{
		pthread_join(philo[i].tr, NULL);
		i++;
	}
}


int main(int argc, char **argv)
{
	t_infos	*glob;
	pthread_t	gard;

	glob = NULL;
	if (argc < 5 || argc > 6)
	{
		write (2, "invalid number of arguments\n", 29);
		return (1);
	}
	init_glob(&glob, argv);
	init_philos(&glob->philos, glob);
	create_threads(&glob);
	pthread_create(&gard, NULL, gard_routine, glob);
	join_threads(glob->philos);
	pthread_join(gard, NULL);
	free_all(&glob);
	return (0);
}
