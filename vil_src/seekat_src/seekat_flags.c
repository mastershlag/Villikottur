#include "vil.h"

static void	get_him_out(t_stock* stock, int i)
{
	char *mem = stock->dirt[i];
	i--;
	while (stock->dirt[++i])
	{
		if (stock->dirt[i + 1])
			stock->dirt[i] = stock->dirt[i + 1];
		else
			stock->dirt[i] = 0;
	}
	free(mem);
}

int			flagchecker(t_stock* stock)
{
	int i = -1;

	while (stock->dirt[++i])
	{
		if (stock->dirt[i][0] == '-')
		{
			#ifdef __linux__
			if (!strcmp(stock->dirt[i], "-elf"))
			{
				only_elf = 1;
				everyone = 0;
				get_him_out(stock, i);
				i--;
			}
			#endif
			#ifdef __APPLE__
			if (!strcmp(stock->dirt[i], "-macho"))
			{
				only_macho = 1;
				everyone = 0;
				get_him_out(stock, i);
				i--;
			}
			#endif
			else if (!strcmp(stock->dirt[i], "-exe"))
			{
				only_exe = 1;
				everyone = 0;
				get_him_out(stock, i);
				i--;
			}
			else if (!strcmp(stock->dirt[i], "-so"))
			{
				only_so = 1;
				everyone = 0;
				get_him_out(stock, i);
				i--;
			}
			else if (!strcmp(stock->dirt[i], "-v"))
			{
				visual = 1;
				get_him_out(stock, i);
				i--;
			}
		}
	}
	if (!stock->dirt[0])
	{
		if (!(stock->dirt[0] = (char*)malloc(sizeof(char) * 5)))
		{
			if (visual)
				printf("damn malloc\n");
			return (1);
		}
		stock->dirt[0] = strcpy(stock->dirt[0], "/tmp");
	}
	return (0);
}
