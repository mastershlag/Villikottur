#include "vil.h"

off_t		PaddingFinder_shdr_32(void *ptr)
{   
	Elf32_Ehdr	*ehdr		= (Elf32_Ehdr *) ptr;
	u_int16_t	shnum 		= ehdr->e_shnum;
	Elf32_Shdr *shdr = (Elf32_Shdr *)(ptr + ehdr->e_shoff);

	off_t previous = 0;
	off_t current = 0;
	int i;
	for (i = 1 ; i < shnum ; ++i)
	{
		previous = shdr[i - 1].sh_offset + shdr[i - 1].sh_size;
		current = shdr[i].sh_offset;
		if (!previous|| previous > current)
			continue;
		if ((current - previous) > strlen(message))
			return (previous);
	}
	return 0;
}
