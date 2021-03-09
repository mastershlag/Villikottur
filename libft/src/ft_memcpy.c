#include "libmaster.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*cpdest;
	char	*cpsrc;
	size_t	cpt;

	cpt = -1;
	if (n == 0 || src == dest)
		return (dest);
	cpdest = (char*)dest;
	cpsrc = (char*)src;
	while (++cpt < n)
		cpdest[cpt] = cpsrc[cpt];
	return (dest);
}
