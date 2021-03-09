#include "libmaster.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*cps1;
	unsigned const char	*cps2;
	size_t				cpt;

	cpt = -1;
	cps1 = s1;
	cps2 = s2;
	while (++cpt < n)
	{
		if (cps1[cpt] != cps2[cpt])
			return (cps1[cpt] - cps2[cpt]);
	}
	return (0);
}
