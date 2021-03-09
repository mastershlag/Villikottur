#include "libmaster.h"

char	*ft_strjoin_free(char *str, char *buff)
{
	char *free_str;

	free_str = str;
	if (!(str = ft_strjoin(str, buff)))
		return (0);
	if (free_str)
		free(free_str);
	return (str);
}

char	*ft_strjoin_eerf(char *str, char *buff)
{
	char *free_str;

	free_str = buff;
	if (!(buff = ft_strjoin(str, buff)))
		return (0);
	if (free_str)
		free(free_str);
	return (buff);
}

char	*ft_strjoin_ufree(char *str, char *buff)
{
	char *free_str;

	free_str = str;
	if (!(str = ft_strjoin(str, buff)))
		return (0);
	free(free_str);
	free(buff);
	return (str);
}
