#include "libmaster.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *out;

	if (!s1 || !s2)
		return (0);
	if (!(out = (char *)malloc(sizeof(char)
		* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	ft_strcpy(out, s1);
	ft_strcat(out, s2);
	return (out);
}
