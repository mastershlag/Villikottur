#include "libmaster.h"

void	ft_bzero(void *s, size_t nbyte)
{
	char	*saviour;
	size_t	john;

	john = -1;
	saviour = s;
	while (++john < nbyte)
		saviour[john] = 0;
}
