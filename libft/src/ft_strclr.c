#include "libmaster.h"

void	ft_strclr(char *s)
{
	if (s)
	{
		while (*s)
			*(s++) = 0;
	}
}

int		ft_strchri(const char *s, int c)
{
	int i;

	i = 0;
	if (c == 0)
		return (ft_strlen(s));
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_strrchri(const char *s, int c)
{
	int i;

	i = ft_strlen(s) - 1;
	if (c == 0)
		return (ft_strlen(s));
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i--;
	}
	return (-1);
}
