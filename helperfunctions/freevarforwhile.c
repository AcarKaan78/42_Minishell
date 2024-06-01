/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freevarforwhile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:13:37 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:26:57 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	preparewhile2(t_data *dat)
{
	dat->parsererrorcode = 0;
	g_global.error = 0;
	g_global.execstatus = 0;
	dat->errorstatus = 0;
	dat->commandcount = 0;
	dat->commandline = NULL;
	dat->arguments = NULL;
	dat->parts = NULL;
}

void	prep_parts_red(t_data *dat)
{
	int	a;
	int	b;

	b = 0;
	a = 0;
	while (dat->parts[a].type != NULL)
	{
		if (dat->parts[a].red)
		{
			while (dat->parts[a].red[b].type)
			{
				free(dat->parts[a].red[b].str);
				dat->parts[a].red[b].str = NULL;
				free(dat->parts[a].red[b].type);
				dat->parts[a].red[b++].type = NULL;
			}
			b = 0;
			free(dat->parts[a].red);
			dat->parts[a].red = NULL;
		}
		ft_frdblpoi(dat->parts[a].str);
		free(dat->parts[a].type);
		a++;
	}
	free(dat->parts);
}

void	ft_pprawhile(t_data *dat)
{
	if (dat->commandline && dat->commandline[0])
	{
		free(dat->commandline);
		if (dat->arguments)
		{
			ft_frdblpoi(dat->arguments);
		}
		if (dat->parts)
		{
			prep_parts_red(dat);
		}
	}
	preparewhile2(dat);
}
