#include "libmaster.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cps;
	size_t			cpt;

	cpt = -1;
	cps = (unsigned char *)s;
	while (++cpt < n)
	{
		if (cps[cpt] == (unsigned char)c)
			return (cps + cpt);
	}
	return (0);
}
