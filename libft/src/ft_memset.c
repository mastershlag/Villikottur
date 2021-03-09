#include "libmaster.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*saviour;
	size_t	john;

	john = -1;
	saviour = str;
	while (++john < n)
		saviour[john] = c;
	return (str);
}
