#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	sign;

	sign = 1;
	n = 0;
	i = 0;
	if ((str[i] <= 47 || str[i] >= 58) && str[i] != '\t' && str[i] != '\n'
		&& str[i] != '\v' && str[i] != '\f' && str[i] != '\r' && str[i] != ' '
		&& str[i] != 45 && str[i] != 43)
		return (0);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' \
	|| str[i] == '\r' || str[i] == ' ')
		i = i + 1;
	if (str[i] == 45)
	{
		sign = -1 ;
		i = i + 1;
	}
	else if (str[i] == 43)
		i = i + 1;
	while ((str[i] != '\0') && (str[i] >= 48 && str [i] <= 57))
		n = n * 10 + (str[i++] - '0');
	return (sign * n);
}
