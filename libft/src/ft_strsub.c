#include "libmaster.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;

	i = -1;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (0);
	if (!(out = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (++i < len && s[start])
		out[i] = s[start++];
	out[i] = '\0';
	return (out);
}
