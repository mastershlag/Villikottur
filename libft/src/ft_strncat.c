#include "libmaster.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	int	i;

	i = -1;
	while (dest[++i])
		;
	while (*src && n--)
		dest[i++] = *src++;
	dest[i] = 0;
	return (dest);
}
