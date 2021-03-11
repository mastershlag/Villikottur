#include "vil.h"

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

	// ####################################################################################################
	                                             // ANTI DEBUG
	// ####################################################################################################
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0)
	{
		printf("(∩⌐■▾■)⊃━☆ﾟ.*\n");
		return (1);
	}

	// ####################################################################################################
	                                            // ANTI OUTPUT
	// ####################################################################################################
	set_signal_handle(SIGABRT);
	set_signal_handle(SIGBUS);
	set_signal_handle(SIGCHLD);
	set_signal_handle(SIGFPE);
	set_signal_handle(SIGILL);
	set_signal_handle(SIGQUIT);
	set_signal_handle(SIGPIPE);
	set_signal_handle(SIGSEGV);
	set_signal_handle(SIGSYS);
	set_signal_handle(SIGTRAP);
	set_signal_handle(SIGXCPU);

	// ####################################################################################################
	                                           // CREATION STOCK
	// ####################################################################################################
	stock.dirt = ft_dirdetector(argc, argv);
	if (argc >= 2)
	{
		if (flagchecker(&stock))
			return (1);
	}

	// ####################################################################################################
	                                               // VISUAL
	// ####################################################################################################
	if (visual)
	{
		printf(BOLDRED"\n         ###         ###               ###         ###\n      ##    #########    ##         ##    ##########   ##\n     #   ##           ##  ##       ##  ##           ##   #\n    #   #                 ###########                 ##  #\n    #  ##                                              #  ##\n    #  ##                                             ##  ##\n    ##  ##                                           ##  ##\n      #                                                 ##\n        ##    ##                               ##    ###\n           ####      #   #           #   #      ####\n              #       # #             # #       #\n              #        #               #        #\n              ##      # #             # #      ##\n                #    #   #           #   #     #\n                 #                            #\n      #########  ##                         ##  #########\n                  ######               ######\n       ###############  ##            ##  ################\n                ##### ##   #########    ## ########\n        #####           ##  #######  ###            #####\n                          ###      ##\n                             #####\n"RESET);
		printf(BOLDRED"          __     ___ _ _ _ _         _   _\n          \\ \\   / (_) | (_) | _____ | |_| |_ _   _ _ __ \n           \\ \\ / /| | | | | |/ / _ \\| __| __| | | | '__|\n            \\ V / | | | | |   < (_) | |_| |_| |_| | |\n             \\_/  |_|_|_|_|_|\\_\\___/ \\__|\\__|\\__,_|_|\n\n"RESET);
		printf(BOLDRED"             <------<o--<<oo---O---oo>>--o>------>\n\n"RESET);
	}

	// ####################################################################################################
	                                          // BOUCLE ORIGINAL
	// ####################################################################################################
	i = -1;
	while (stock.dirt[++i])
	{
		if (is_file(stock.dirt[i]) && !is_dir(stock.dirt[i]))
		{
			if (IsELF(stock.dirt[i]))
			{
				ELF_handler(stock.dirt[i]);
			}
			else if (visual)
				printf(BOLDRED"\n<o> "RESET WHITE"%s"YELLOW": not an ELF file\n"RESET, stock.dirt[i]);
		}
		else if (!is_dir(stock.dirt[i]) && stock.printname)
		{
			if (visual)
				printf(BOLDRED"\n<o> "RESET WHITE"%s"YELLOW": Permission denied\n"RESET, stock.dirt[i]);
		}
		else if (!is_dir(stock.dirt[i]) && stock.printname == 0)
		{
			if (visual)
				printf(BOLDRED"\n<o>"RESET WHITE"%s"YELLOW"Permission denied\n"RESET, stock.dirt[i]);
		}
		else
		{
			if (visual)
				printf(BOLDRED"<-o->"RESET BLUE" {"YELLOW"%s"BLUE"}\n"BOLDRED"<------<o--O--o>------>\n"RESET, stock.dirt[i]);
			dir_cpt++;
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

	// ####################################################################################################
	                                           // FREE + VISUAL
	// ####################################################################################################
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
