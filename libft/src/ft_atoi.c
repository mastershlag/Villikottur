#include "libmaster.h"

int			ft_mastoi(const char *str)
{
	long long int			out;
	int						flag;

	flag = 1;
	out = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		flag = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			out = out * 10 + ((long long int)*str - '0');
		else
			return (0);
		str++;
	}
	return (out * flag);
}

int			ft_atoi(const char *str)
{
	long long int			out;
	int						flag;

	flag = 1;
	out = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		flag = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			out = out * 10 + ((long long int)*str - '0');
		else
			return (out * flag);
		str++;
	}
	return (out * flag);
}

long long	ft_ultimatoi(const char *str)
{
	long long int			out;
	int						flag;

	flag = 1;
	out = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		flag = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			out = out * 10 + ((long long int)*str - '0');
		else
			return (0);
		str++;
	}
	return (out * flag);
}
