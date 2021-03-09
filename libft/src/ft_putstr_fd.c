#include "libmaster.h"

void	ft_putstr_fd(char const *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putnstr_fd(char const *s, int fd, int n)
{
	int gg;

	if (!s)
		return ;
	gg = ft_strlen(s);
	if (n < 0)
		return ;
	if (n > gg)
		n = gg;
	write(fd, s, n);
}
