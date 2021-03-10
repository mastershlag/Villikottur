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
