#include "libmaster.h"

int	ft_isalnum(int c)
{
	return ((ft_isdigit(c) || ft_isalpha(c)) ? 1 : 0);
}

int	ft_isalnumflt(int c)
{
	return ((ft_isdigit(c) || ft_isalpha(c) || c == '.') ? 1 : 0);
}
