#include "philo_bonus.h"

void	init_glob(t_infos **glob, char **argv)
{
	t_infos	*res;

	res = malloc (sizeof(t_infos));
	if (!res)
		error_malloc();
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
	if (!res->philos)
		error_malloc();
	*glob = res;
}

int	main(int argc, char **argv)
{
	t_infos		*glob;

	glob = NULL;
	if (argc < 5 || argc > 6)
	{
		write (2, "invalid number of arguments\n", 29);
		return (1);
	}
	check_valid_args(argv + 1);
	init_glob(&glob, argv);
	init_philos(&glob->philos, glob);
	create_threads(&glob);
	join_threads(glob->philos);
	free_all(&glob);
	return (0);
}