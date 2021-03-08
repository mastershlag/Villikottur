/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vil_tools_linux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 18:37:01 by paulo             #+#    #+#             */
/*   Updated: 2021/03/08 15:01:36 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vil.h"

int		IsSO_or_EXEC(char *name)
{
	int			fd;
	int			ret;
	char		*ptr;
	struct stat	buf;

	if ((fd = open(name, O_RDONLY)) < 0)
		return (0);
	if (fstat(fd, &buf) < 0)
		return (0);
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (0);
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *) ptr;
	if (ehdr->e_type == ET_REL || ehdr->e_type == ET_CORE)
    	return (0);
	else if (ehdr->e_type == ET_DYN )
		ret = 1;
	else if (ehdr->e_type == ET_EXEC)
		ret = 2;
	if (munmap(ptr, buf.st_size) < 0)
		return (0);
	if (close(fd) < 0)
		return (0);
	return (ret);
}
