/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vil.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:01:03 by pharatyk          #+#    #+#             */
/*   Updated: 2021/03/08 16:14:17 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEEKAT_H
# define SEEKAT_H

# include "libmaster.h"
# include "color.h"
# include <stdio.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <time.h>
# include <grp.h>
# include <pwd.h>
# include <sys/ioctl.h>
# include <sys/mman.h>

# ifdef __linux__
 #include <elf.h>
# endif

# define MAGIC_ELF		"\x7f\x45\x4c\x46"
# define MAGIC_MACHO1	"\xfe\xed\xfa\xce"
# define MAGIC_MACHO2	"\xfe\xed\xfa\xcf"
# define MAGIC_MACHO3	"\xca\xfe\xba\xbe"
# define MAGIC_MACHO4	"\xce\xfa\xed\xfe"
# define MAGIC_MACHO5	"\xcf\xfa\xed\xfe"

int file_cpt;
int dir_cpt;
int elf_cpt;
int macho_cpt;
int exec_cpt;
int so_cpt;

int	everyone;
int	only_elf;
int	only_macho;
int	only_exe;
int	only_so;
int visual;


typedef struct	s_stock
{
	char	**dirt;
	char	**output;
	int		printname;
}				t_stock;

typedef struct	s_basiks
{
	int		max;
	int		nbobj;
	int		nbligne;
	int		lignemax;
}				t_basiks;


char			**ft_dirdetector(int c, char **v);
int				ft_printer(t_stock *stock, int lvl);
int				ft_basic(t_stock *stock);
void			free_stock(t_stock *stock);
int				ft_sonar(t_stock *stock, int i);
int				is_dir(char *name);
int				is_file(char *name);
void			print_stock(t_stock *stock);
int				is_truedir(char *test);
int				ft_islink(char *path, char **buf, int ret);
int				IsELF(char *name);
int				IsSO_or_EXEC(char *name);
int				IsMachO(char *name);
void			free_dirt(t_stock *stock);
void			free_output(t_stock *stock);

#endif
