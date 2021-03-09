#include "libmaster.h"

void	*ft_memalloc(size_t size)
{
	void	*out;

	if (!(out = malloc(size)))
		return (0);
	ft_bzero(out, size);
	return (out);
}
