#include "philosophers.h"

t_infos	init_struct(char **argv)
{
	t_infos	res;

	res.n_philos = ft_atoi(argv[1]);
	res.time_to_d = ft_atoi(argv[2]);
	res.time_to_e = ft_atoi(argv[3]);
	res.time_to_s = ft_atoi(argv[4]);
	if (argv[4])
		res.num_times_eat = ft_atoi(argv[5]);
	else
		res.num_times_eat = -1;
	return (res);
}

int main(int argc, char **argv)
{
	t_infos	infos;

	if (argc < 5 || argc > 6)
	{
		write (2, "invalid number of arguments\n", 29);
		return (1);
	}
	infos = init_struct(argv);
}