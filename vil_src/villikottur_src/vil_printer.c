/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vil_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 13:58:06 by pharatyk          #+#    #+#             */
/*   Updated: 2021/03/09 12:19:27 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vil.h"

static int	ft_addpath(char *output, char *path, char **tmp)
{
	if (!ft_strcmp(path, "/"))
	{
		if (!(tmp[0] = (char*)malloc(sizeof(char) * (ft_strlen(output) + 2))))
			return (1);
		tmp[0][ft_strlen(output) + 1] = 0;
		tmp[0] = ft_strcpy(tmp[0], path);
		tmp[0] = ft_strcat(tmp[0], output);
		return (0);
	}
	if (!(tmp[0] = (char*)malloc(sizeof(char) * (ft_strlen(path)
						+ ft_strlen(output) + 2))))
		return (1);
	tmp[0][ft_strlen(path) + ft_strlen(output) + 1] = 0;
	tmp[0] = ft_strcpy(tmp[0], path);
	tmp[0] = ft_strcat(tmp[0], "/");
	tmp[0] = ft_strcat(tmp[0], output);
	return (0);
}

static int	ft_printerrdir(t_stock *explorer, char *tmp)
{
	if (visual)
		printf(BOLDRED"\n<-o->"RESET BLUE" {"YELLOW"%s"BLUE"}\n"BOLDRED"<------<o--O--o>------>\n"RESET, tmp);
	if (!(explorer->dirt = (char**)malloc(sizeof(char*) * 2)))
		return (1);
	explorer->dirt[1] = 0;
	if (!(explorer->dirt[0] = (char*)malloc(sizeof(char)
					* (ft_strlen(tmp) + 1))))
		return (1);
	explorer->dirt[0][ft_strlen(tmp)] = 0;
	explorer->dirt[0] = ft_strcpy(explorer->dirt[0], tmp);
	explorer->printname = 0;
	if (ft_sonar(explorer, 0))
		return (1);
	free_stock(explorer);
	return (0);
}

int			ft_printer(t_stock *stock, int lvl)
{
	int		i;
	char	*tmp;
	t_stock	explorer;
	char	*buf;

	i = -1;
	while (stock->output[++i])
	{
		if (ft_addpath(stock->output[i], stock->dirt[lvl], &tmp))
			return (1);
		if (is_dir(tmp) && tmp[ft_strlen(stock->dirt[lvl]) + ft_strlen(stock->output[i])] != '.'
			&& tmp[ft_strlen(stock->dirt[lvl]) + ft_strlen(stock->output[i])] != '/'
			&& !ft_islink(tmp, &buf, 0))
		{
			dir_cpt++;
			if (ft_printerrdir(&explorer, tmp))
				return (1);
		}
		else if (!is_dir(tmp) && is_truedir(tmp))
		{
			if (visual)
				printf("\n%s\nft_ls: %s: Permission denied\n" , tmp, stock->output[i]);
		}
		else if (is_file(tmp) && !is_dir(tmp))
		{
			if (IsELF(tmp))
			{
				int ret = IsSO_or_EXEC(tmp);
				if (ret == 1)
				{
					if ((everyone || only_so) && visual)
						printf(BOLDRED"<"BOLDCYAN"o"BOLDRED"> "RESET BLUE"{"YELLOW"%s"BLUE"}\n"RESET, tmp);
					so_cpt++;
				}
				else if (ret == 2)
				{
					if ((everyone || only_exe) && visual)
						printf(BOLDRED"<"BOLDGREEN"o"BOLDRED"> "RESET BLUE"{"YELLOW"%s"BLUE"}\n"RESET, tmp);
					exec_cpt++;
				}
				else if ((everyone || only_elf) && visual)
						printf(BOLDRED"<o> "RESET BLUE"{"YELLOW"%s"BLUE"}\n"RESET, tmp);
				file_checker(tmp);
				elf_cpt++;
			}
			else if (IsMachO(tmp))
			{
				if ((everyone || only_macho) && visual)
					printf(BOLDMAGENTA"<o> "RESET BLUE"{"YELLOW"%s"BLUE"}\n"RESET, tmp);
				macho_cpt++;
			}
			else if (everyone && visual)
				printf(BOLDWHITE"<o> "RESET BLUE"{"YELLOW"%s"BLUE"}\n"RESET, tmp);
			file_cpt++;
		}
		free(tmp);
	}
	return (0);
}
