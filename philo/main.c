#include "philosophers.h"

t_infos	init_struct(char **argv)
{
	t_infos	res;

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
	res.died = 0;
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

void	create_threads(t_infos *infos)
{
	int	i;
	static pthread_t	*pids;

	i = 0;
	pids = malloc(sizeof(pthread_t) * infos->n_philos);
	pthread_mutex_t		zz;
	pthread_mutex_init(&zz, NULL);
	while (i < infos->n_philos)
	{
		int *arg = malloc(sizeof(int));
		*arg = i;
		pthread_create(&pids[i], NULL, handel_threads, arg);
		i++;
	}
	i = 0;
	while (i < infos->n_philos)
	{
		pthread_join(pids[i], NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_infos	infos;

	if (argc < 5 || argc > 6)
	{
		write (2, "invalid number of arguments\n", 29);
		return (1);
	}
	check_valid_args(argv + 1);
	infos = init_struct(argv);
	create_threads(&infos);
	return (0);
}
