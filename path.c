/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:29:47 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:20:00 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_findpth(char *searchpath, t_data *dat)
{
	int		a;
	char	*foundedpath;

	a = 0;
	while (dat->path[a])
	{
		foundedpath = ft_strjoin2(dat->path[a], "/");
		foundedpath = ft_strjoin(foundedpath, searchpath);
		if (access(foundedpath, F_OK) == 0)
		{
			dat->foundedpath = foundedpath;
			return (1);
		}
		a++;
		free(foundedpath);
	}
	return (0);
}

int	ft_pathind(char *searchpath, t_data *dat)
{
	int	a;

	a = 0;
	while (dat->path[a])
	{
		if (!ft_strcmp(dat->path[a], searchpath))
			return (a);
		a++;
	}
	return (-1);
}

int	ft_fndindvp(char *srcenvp, int srcind, t_data *dat)
{
	int	a;

	a = 0;
	while (dat->envp[a])
	{
		if (ft_strncmp(dat->envp[a], srcenvp, srcind) == 0)
			return (a);
		a++;
	}
	return (-1);
}

int	ft_fndexpind(char *srchedexportp, int srcind, t_data *dat)
{
	int	a;

	a = 0;
	while (dat->exportp[a])
	{
		if (ft_strncmp(dat->exportp[a], srchedexportp, srcind) == 0)
			return (a);
		a++;
	}
	return (-1);
}
