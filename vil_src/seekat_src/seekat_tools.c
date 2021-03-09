#include "vil.h"

int		is_truedir(char *test)
{
	struct stat	lol;

	stat(test, &lol);
	return ((S_ISDIR(lol.st_mode) ? 1 : 0));
}

int		ft_islink(char *path, char **buf, int ret)
{
	int bufsiz;

	bufsiz = 255;
	if (!(buf[0] = (char*)malloc(sizeof(char) * (bufsiz + 1))))
		return (0);
	bufsiz = readlink(path, buf[0], bufsiz);
	if (bufsiz == -1)
	{
		free(buf[0]);
		return (0);
	}
	else if (ret)
		buf[0][bufsiz] = 0;
	else if (!ret)
		free(buf[0]);
	return (1);
}

void	free_dirt(t_stock *stock)
{
	int	i;

	i = -1;
	if (stock->dirt)
	{
		while (stock->dirt[++i])
			free(stock->dirt[i]);
		free(stock->dirt[i]);
		free(stock->dirt);
	}
}

void	free_output(t_stock *stock)
{
	int	i;

	i = -1;
	if (stock->output)
	{
		while (stock->output[++i])
			free(stock->output[i]);
		free(stock->output[i]);
		free(stock->output);
	}
}


void	free_stock(t_stock *stock)
{
	int	i;

	i = -1;
	if (stock->dirt)
	{
		while (stock->dirt[++i])
			free(stock->dirt[i]);
		free(stock->dirt[i]);
		free(stock->dirt);
	}
	i = -1;
	if (stock->output)
	{
		while (stock->output[++i])
			free(stock->output[i]);
		free(stock->output[i]);
		free(stock->output);
	}
}

int		is_dir(char *name)
{
	DIR	*pdir;
	int	flag;

	pdir = opendir(name);
	if (pdir == NULL)
		flag = 0;
	else
	{
		flag = 1;
		closedir(pdir);
	}
	return (flag);
}

int		is_file(char *name)
{
	struct stat	st;

	return ((stat(name, &st) < 0) ? 0 : 1);
}

int		IsELF(char *name)
{
	int fd = open(name, O_RDONLY);
	if (fd == -1)
		return 0;

	char magic[4];
	int bytes_read = read(fd, magic, 4);
	if (bytes_read != 4 )
	{
		close(fd);
		return 0;
	}
	if (strncmp(magic, MAGIC_ELF, 4) != 0)
	{
		close(fd);
		return 0;
	}
	close(fd);
	return 1;
}

int		IsMachO(char *name)
{
	int fd = open(name, O_RDONLY);
	if (fd == -1)
		return 0;

	char magic[4];
	int bytes_read = read(fd, magic, 4);
	if (bytes_read != 4 )
	{
		close(fd);
		return 0;
	}
	if (strncmp(magic, MAGIC_MACHO1, 4) != 0 && strncmp(magic, MAGIC_MACHO2, 4) != 0
		&& strncmp(magic, MAGIC_MACHO3, 4) != 0 && strncmp(magic, MAGIC_MACHO4, 4) != 0
		&& strncmp(magic, MAGIC_MACHO5, 4) != 0)
	{
		close(fd);
		return 0;
	}
	close(fd);
	return 1;
}
