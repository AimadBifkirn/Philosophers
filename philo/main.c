#include "philosophers.h"

t_infos	init_struct(char **argv)
{
	t_infos	res;

	res.start_time = get_time();
	res.n_philos = ft_atoi(argv[1]);
	if (res.n_philos == 0 || res.n_philos > 200)
	{
		write (2, "invalid philos number !\n", 25);
		exit (1);
	}
	res.time_to_d = ft_atoi(argv[2]);
	res.time_to_e = ft_atoi(argv[3]);
	res.time_to_s = ft_atoi(argv[4]);
	if (argv[5])
		res.num_times_eat = ft_atoi(argv[5]);
	else
		res.num_times_eat = -1;
	res.died = 1;
	res.forks = forks_init(res.n_philos);
	pthread_mutex_init(&res.print_lock, NULL);
	pthread_mutex_init(&res.data_lock, NULL);
	return (res);
}

void	*handel_threads(void *i)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	printf ("%ld\t", time.tv_sec);
	printf ("this is philosofer %d\n", *((int *)i) + 1);
	free (i);
	return (NULL);
}

void	join_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->infos->n_philos)
	{
		pthread_join(philo[i].tr, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_infos	infos;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
	{
		write (2, "invalid number of arguments\n", 29);
		return (1);
	}
	infos = init_struct(argv);
	philo = init_philo(&infos);
	check_valid_args(argv + 1);
	// create_philos_threads(&infos);
	join_threads(philo);
	// clear_all(); to code later.
	return (0);
}
