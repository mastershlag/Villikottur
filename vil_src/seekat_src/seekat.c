#include "vil.h"

static char	*ft_ona(char *lol)
{
	int i;
	int j;
	int safety;

	i = -1;
	j = 0;
	safety = 0;
	while (lol[++i])
		if (lol[i] == '/')
		{
			j = i + 1;
			safety = 1;
		}
	if (safety)
		return (lol + j);
	return (lol);
}

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

// static void	print_stock2(t_stock *stock)
// {
// 	int i;

// 	printf("\n<<-------<>------->>\n");
// 	i = -1;
// 	while(stock->dirt[++i])
// 		printf("dirt[%2d] : {%s}\n", i, stock->dirt[i]);
// 	printf("<<-------<>------->>\n");
// 	i = -1;
// 	while(stock->output[++i])
// 		printf("output[%2d] : {%s}\n", i, stock->output[i]);
// 	printf("<<-------<>------->>\n");
// 	printf("\n");
// }

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
	// print_stock2(stock);
	if (ft_printer(stock, i))
		return (1);
	return (0);
}

void		get_him_out(t_stock* stock, int i)
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

int		flagchecker(t_stock* stock)
{
	int i = -1;

	while (stock->dirt[++i])
	{
		if (stock->dirt[i][0] == '-')
		{
			#ifdef __linux__
			if (!ft_strcmp(stock->dirt[i], "-elf"))
			{
				only_elf = 1;
				everyone = 0;
				get_him_out(stock, i);
				i--;
			}
			#endif
			#ifdef __APPLE__
			if (!ft_strcmp(stock->dirt[i], "-macho"))
			{
				only_macho = 1;
				everyone = 0;
				get_him_out(stock, i);
				i--;
			}
			#endif
			else if (!ft_strcmp(stock->dirt[i], "-exe"))
			{
				only_exe = 1;
				everyone = 0;
				get_him_out(stock, i);
				i--;
			}
			else if (!ft_strcmp(stock->dirt[i], "-so"))
			{
				only_so = 1;
				everyone = 0;
				get_him_out(stock, i);
				i--;
			}
			else if (!ft_strcmp(stock->dirt[i], "-v"))
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
		stock->dirt[0] = ft_strcpy(stock->dirt[0], "/tmp");
	}
	return (0);
}

int			main(int argc, char *argv[])
{
	int		i;
	t_stock	stock;

	// COUNT STUFF
	// #############
	file_cpt	= 0;
	dir_cpt		= 0;
	elf_cpt		= 0;
	macho_cpt	= 0;
	exec_cpt	= 0;
	so_cpt		= 0;
	// #############

	// FLAG STUFF
	// #############
	everyone	= 1;
	only_elf	= 0;
	only_macho	= 0;
	only_exe	= 0;
	only_so		= 0;
	visual		= 0;
	// #############


	stock.dirt = ft_dirdetector(argc, argv);
	if (argc >= 2)
	{
		if (flagchecker(&stock))
			return (1);
	}

	if (visual)
	{
		printf(BOLDRED"\n         ###         ###               ###         ###\n      ##    #########    ##         ##    ##########   ##\n     #   ##           ##  ##       ##  ##           ##   #\n    #   #                 ###########                 ##  #\n    #  ##                                              #  ##\n    #  ##                                             ##  ##\n    ##  ##                                           ##  ##\n      #                                                 ##\n        ##    ##                               ##    ###\n           ####      #   #           #   #      ####\n              #       # #             # #       #\n              #        #               #        #\n              ##      # #             # #      ##\n                #    #   #           #   #     #\n                 #                            #\n      #########  ##                         ##  #########\n                  ######               ######\n       ###############  ##            ##  ################\n                ##### ##   #########    ## ########\n        #####           ##  #######  ###            #####\n                          ###      ##\n                             #####\n"RESET);
		printf(BOLDRED"          __     ___ _ _ _ _         _   _\n          \\ \\   / (_) | (_) | _____ | |_| |_ _   _ _ __ \n           \\ \\ / /| | | | | |/ / _ \\| __| __| | | | '__|\n            \\ V / | | | | |   < (_) | |_| |_| |_| | |\n             \\_/  |_|_|_|_|_|\\_\\___/ \\__|\\__|\\__,_|_|\n\n"RESET);
		printf(BOLDRED"             <------<o--<<oo---O---oo>>--o>------>\n\n"RESET);
	}

	i = -1;
	while (stock.dirt[++i])
	{
		if (!is_dir(stock.dirt[i]) && stock.printname)
		{
			if (visual)
				printf("%s:\nft_ls: %s: Permission denied\n" , stock.dirt[i], ft_ona(stock.dirt[i]));
		}
		else if (!is_dir(stock.dirt[i]) && stock.printname == 0)
		{
			if (visual)
				printf("ft_ls: %s: Permission denied\n", ft_ona(stock.dirt[i]));
		}
		else
		{
			if (visual)
				printf(BOLDRED"<-o->"RESET BLUE" {"YELLOW"%s"BLUE"}\n"BOLDRED"<------<o--O--o>------>\n"RESET, stock.dirt[i]);
			if (ft_sonar(&stock, i))
			return (1);
			free_output(&stock);
		}
		if (stock.dirt[i + 1])
		{
			if (visual)
				printf("\n");
		}
	}
	free_dirt(&stock);
	if (visual)
	{
		printf(BOLDRED"<------<o--<<oo---O---oo>>--o>------>\n"RESET);
		printf(YELLOW"Checked "BOLDWHITE"%d "RESET YELLOW"files in "BOLDWHITE"%d"RESET YELLOW" directories \n"RESET, file_cpt, dir_cpt);
		printf(YELLOW"Found "BOLDRED"%d "RESET YELLOW"ELF with "BOLDCYAN"%d"RESET YELLOW" SO and "BOLDGREEN"%d"RESET YELLOW" EXEC\n"RESET, elf_cpt, so_cpt, exec_cpt);
		printf(YELLOW"Found "BOLDMAGENTA"%d "RESET YELLOW"Mach-O\n"RESET, macho_cpt);
	}
	return (0);
}
