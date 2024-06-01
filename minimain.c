/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellmain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:29:04 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:30:37 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmdfndv2(t_data *dat)
{
	int	a;
	int	tr;

	tr = 0;
	a = 0;
	while (ft_strcmp(dat->parts[a].type, "pipe") && dat->parts[a + 1].type)
	{
		a++;
	}
	if (!ft_strcmp(dat->parts[a].type, "pipe") && dat->parts[a + 1].type)
	{
		ft_chiledfpi(&(dat->parts[a - 1]), &(dat->parts[a + 1]), dat);
	}
	else
	{
		ft_output_all(&(dat->parts[0]), dat);
	}
}

void	startprogram2(t_data *dat)
{
	dat->commandline = readline(dat->starttext);
	if (dat->commandline == NULL)
		ft_ifsend(dat);
	if (ft_strcmp(dat->commandline, ""))
		add_history(dat->commandline);
	else
		free(dat->commandline);
	ft_quoterr(dat);
}

void	startprogram(t_data *dat)
{
	while (1)
	{
		startprogram2(dat);
		if (dat->errorstatus == 0 && dat->commandline[0])
		{
			ft_parsermain(dat);
			if (dat->parsererrorcode == 0 && g_global.error == 0)
			{
				ft_trndol(dat, 0);
				dat->exitstatus = 127;
				ft_rmvquo(dat);
				dat->parts = ft_endpars(dat->arguments, 1, -1, dat);
				ft_cmdfndv2(dat);
			}
			else if (dat->parsererrorcode != 3 && g_global.error == 0)
			{
				printf("> bash: syntax error: unexpected end of file\n");
				dat->exitstatus = 258;
			}
		}
		ft_pprawhile(dat);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*dat;

	dat = malloc(sizeof(t_data));
	signal(SIGINT, ft_ifsigint);
	signal(SIGQUIT, ft_sndquit);
	del_ctr();
	ft_initfunc(envp, argc, argv, dat);
	startprogram(dat);
	return (0);
}
