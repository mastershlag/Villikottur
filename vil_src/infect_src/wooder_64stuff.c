#include "vil.h"

off_t		PaddingFinder_shdr_64(void *ptr)
{   
	Elf64_Ehdr	*ehdr		= (Elf64_Ehdr *) ptr;
	u_int16_t	shnum 		= ehdr->e_shnum;
	Elf64_Shdr *shdr = (Elf64_Shdr *)(ptr + ehdr->e_shoff);

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
	return (0);
}

// Elf64_Off	PaddingFinder_64(void *ptr)
// {   
// 	Elf64_Ehdr	*ehdr		= (Elf64_Ehdr *) ptr;
// 	u_int16_t	phnum 		= ehdr->e_phnum;
// 	Elf64_Phdr *phdr = (Elf64_Phdr *)(ptr + ehdr->e_phoff);

// 	u_int16_t TEXT_SEGMENT_FOUND = 0;
// 	Elf64_Off parasite_offset;
// 	int i;
// 	for (i = 0 ; i < phnum ; ++i)
// 	{
// 		if (TEXT_SEGMENT_FOUND  == 0 && phdr[i].p_type  == PT_LOAD &&
// 			phdr[i].p_flags == (PF_R | PF_X))
// 		{
// 			TEXT_SEGMENT_FOUND = 1;
// 			parasite_offset = phdr[i].p_offset + phdr[i].p_filesz;
// 		}
// 		else if (TEXT_SEGMENT_FOUND)
// 		{
// 			if ((phdr[i].p_offset - parasite_offset) > strlen(message))
// 				return (parasite_offset);
// 			return (0);
// 		}
// 	}

// 	return 0;
// }
