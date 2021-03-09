#include "libmaster.h"

char	*ft_strnew(size_t size)
{
	char	*out;

	if (!(out = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_memset(out, '\0', size + 1);
	return (out);
}
