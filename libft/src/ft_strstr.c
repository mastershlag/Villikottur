#include "libmaster.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;

	i = 0;
	if (!(ft_strlen(needle)))
		return ((char *)haystack);
	while (*haystack)
	{
		if (*haystack == needle[0])
		{
			while (haystack[i] == needle[i])
			{
				if (needle[i + 1] == 0)
					return ((char *)haystack);
				i++;
			}
		}
		haystack++;
	}
	return (0);
}
