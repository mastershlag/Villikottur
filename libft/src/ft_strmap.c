#include "libmaster.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*out;
	int		i;

	i = -1;
	if (!s || !f)
		return (0);
	if (!(out = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (0);
	while (s[++i])
		out[i] = f(s[i]);
	out[i] = 0;
	return (out);
}
