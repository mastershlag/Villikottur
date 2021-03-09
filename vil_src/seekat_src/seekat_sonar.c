#include "vil.h"

static int	ft_outputfiller(t_stock *stock, int i)
{
	struct dirent	*pdirent;
	DIR				*pdir;
	int				len;
	int				j;

	if (!(pdir = opendir(stock->dirt[i])))
		return (1);
	j = 0;
	while ((pdirent = readdir(pdir)) != NULL)
		if (pdirent->d_name[0] != '.')
		{
			len = ft_strlen(pdirent->d_name);
			if (!(stock->output[j] = (char*)malloc(sizeof(char) * (len + 1))))
				return (1);
			stock->output[j][len] = 0;
			stock->output[j] = ft_strcpy(stock->output[j], pdirent->d_name);
			j++;
		}
	closedir(pdir);
	return (0);
}

int			ft_sonar(t_stock *stock, int i)
{
	struct dirent	*pdirent;
	DIR				*pdir;
	int				nbdir;

	nbdir = 0;
	if (!(pdir = opendir(stock->dirt[i])))
		return (1);
	while ((pdirent = readdir(pdir)) != NULL)
		if (pdirent->d_name[0] != '.')
			nbdir++;
	closedir(pdir);
	if (!(stock->output = (char**)malloc(sizeof(char*) * (nbdir + 1))))
		return (1);
	stock->output[nbdir] = 0;
	if (ft_outputfiller(stock, i))
		return (1);
	if (ft_printer(stock, i))
		return (1);
	return (0);
}
