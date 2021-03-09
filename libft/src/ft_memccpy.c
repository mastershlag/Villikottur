#include "libmaster.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*cpdest;
	const char	*cpsrc;

	cpdest = dest;
	cpsrc = src;
	while (n--)
	{
		*cpdest = *cpsrc;
		if (*cpdest == (char)c)
			return ((void *)(++cpdest));
		cpdest++;
		cpsrc++;
	}
	return (0);
}
