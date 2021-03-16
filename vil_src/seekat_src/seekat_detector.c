#include "vil.h"

static char	**ft_nodir(void)
{
	char **dirt;

	if (!(dirt = (char**)malloc(sizeof(char*) * (2))))
		return (0);
	dirt[1] = 0;
	if (!(dirt[0] = (char*)malloc(sizeof(char) * 5)))
		return (0);
	dirt[0] = strcpy(dirt[0], "/tmp");
	return (dirt);
}

char		**ft_dirdetector(int argc, char **argv)
{
	char	**dirt;
	int		inc;
	int		test;
	int		i;

	test = 0;
	if (!(dirt = (char**)malloc(sizeof(char*) * argc)))
		return (0);
	dirt[argc - 1] = 0;
	inc = 0;
	i = 0;
	while (argv[++i])
	{
		if (!(dirt[inc] = (char*)malloc(sizeof(char) * (strlen(argv[i]) + 1))))
			return (0);
		dirt[inc] = strcpy(dirt[inc], argv[i]);
		inc++;
		test = 1;
	}
	if (!test)
	{
		free(dirt);
		dirt = ft_nodir();
	}
	return (dirt);
}
