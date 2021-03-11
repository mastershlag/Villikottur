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
# include <sys/ptrace.h>
# include <signal.h>

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

char *message;

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


// ############################################################
                      // SEEKAT_DETECTOR
// ############################################################
char			**ft_dirdetector(int c, char **v);

// ############################################################
                        // SEEKAT_SONAR
// ############################################################
int				ft_sonar(t_stock *stock, int i);

// ############################################################
                       // SEEKAT_PRINTER
// ############################################################
void			ELF_handler(char *tmp);
int				ft_printer(t_stock *stock, int lvl);

// ############################################################
                        // SEEKAT_TOOLS
// ############################################################
char			*ft_ona(char *lol);
void			free_output(t_stock *stock);
void			free_dirt(t_stock *stock);
int				IsMachO(char *name);
int				IsSO_or_EXEC(char *name);
int				IsELF(char *name);
int				is_dir(char *name);
int				is_file(char *name);
int				is_truedir(char *test);
int				ft_islink(char *path, char **buf, int ret);
void			free_stock(t_stock *stock);

// ############################################################
                        // SEEKAT_FLAGS
// ############################################################
int				flagchecker(t_stock* stock);

// ############################################################
                           // WOODER
// ############################################################
int				file_checker(char *filename);

// ############################################################
                        // WOODER_TOOLS
// ############################################################
int				is_32or64ELF(void *ptr);
int				check_copy(char *ptr, size_t size);

// ############################################################
                       // WOODER_32STUFF
// ############################################################
off_t			PaddingFinder_shdr_32(void *ptr);

// ############################################################
                       // WOODER_64STUFF
// ############################################################
off_t     PaddingFinder_shdr_64(void *ptr);

// ############################################################
                           // TOOLS
// ############################################################
void			set_signal_handle(int sig);

#endif
