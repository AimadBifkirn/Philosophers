#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write (2, "invalid number of arguments\n", 29);
		return (1);
	}
	check_valid_args(argv + 1);
	return (0);
}