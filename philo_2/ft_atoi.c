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

void	print_error(char *str)
{
	write (2, "this value is begger then int max :", 36);
	write (2, str, ft_strlen(str));
	write (2, "\n", 1);
	exit (1);
}

void	check_lenght(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			;
		else
			len++;
		i++;
	}
	if (len > 10)
		print_error(str);
}

int	ft_atoi(char *str)
{
	int		i;
	int		s;
	long	result;

	check_lenght(str);
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
	if (result > INT_MAX)
		print_error(str);
	return (result * s);
}
