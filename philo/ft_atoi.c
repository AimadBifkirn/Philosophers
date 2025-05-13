#include "philosophers.h"

static int	space(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

static int	sign(char *str)
{
	int	i;
	int	j;

	i = space(str);
	j = 1;
	if (str[i] == '-')
	{
		j *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (i * j);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	result;

	s = 1;
	i = sign((char *)str);
	if (i < 0)
	{
		s = -1;
		i = -i;
	}
	result = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			break ;
		i++;
	}
	return (result * s);
}
