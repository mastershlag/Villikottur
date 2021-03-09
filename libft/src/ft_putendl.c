#include "libmaster.h"

void	ft_putendl(char const *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
	ft_putchar('\n');
}
