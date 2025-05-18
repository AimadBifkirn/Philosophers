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

void	join_threads(t_philo *philo)
{
	int	i;
	int	num;

	i = 0;
	num = philo->infos->n_philos;
	while (i < num)
	{
		pthread_join(philo[i].tr, NULL);
		i++;
	}
}

void	start_threads(t_philo *philo)
{
	int	num;
	int	i;

	num = philo->infos->n_philos;
	i = 0;
	while (i < num)
	{
		pthread_create(&philo[i].tr, NULL, routine_of_philo, &philo[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_infos	infos;
	t_philo	*philo;
	pthread_t	monitor;

	if (argc < 5 || argc > 6)
	{
		write (2, "invalid number of arguments\n", 29);
		return (1);
	}
	check_valid_args(argv + 1);
	infos = init_struct(argv);
	philo = init_philo(&infos);
	start_threads(philo);
	pthread_create(&monitor, NULL, monitore_routine, philo);
	join_threads(philo);
	pthread_join(monitor, NULL);
	// clear_all(); to code later.
	return (0);
}
