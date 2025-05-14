#include "philosophers.h"

void	check_valid_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (j == 0 && args[i][j] == '+')
				;
			else if (!(args[i][j] >= '0' && args[i][j] <= '9') \
			|| (j == 0 && args[i][j] == '-'))
			{
				write (2, "invalid arguement :", 20);
				write (2, args[i], ft_strlen(args[i]));
				write (2, "\n", 1);
				exit (1);
			}
			j++;
		}
		i++;
	}
}
