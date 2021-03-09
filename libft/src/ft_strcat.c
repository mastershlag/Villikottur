#include "libmaster.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	i;

	i = -1;
	while (dest[++i])
		;
	while (*src)
		dest[i++] = *src++;
	dest[i] = 0;
	return (dest);
}

char	**ft_tabcat(char **dest, char **src)
{
	int	i;

	i = -1;
	while (dest[++i])
		;
	while (*src)
		dest[i++] = *src++;
	dest[i] = 0;
	return (dest);
}

int		*ft_tabintcat(int *dest, int *src)
{
	int	i;

	i = -1;
	while (dest[++i])
		;
	while (*src)
		dest[i++] = *src++;
	dest[i] = 0;
	return (dest);
}

char	**ft_tabcator(char **dest, char **src)
{
	int	i;

	i = -1;
	while (dest[++i])
		;
	while (*src)
	{
		dest[i] = *src;
		*src = 0;
		i++;
		src++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_strcator(char *dest, char *src)
{
	int	i;

	i = -1;
	while (dest[++i])
		;
	while (*src)
	{
		dest[i] = *src;
		*src = 0;
		i++;
		src++;
	}
	dest[i] = 0;
	return (dest);
}
