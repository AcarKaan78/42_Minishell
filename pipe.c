/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:31:05 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:25:06 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_pipe(t_parse *prt)
{
	int	a;

	a = 0;
	while (ft_strcmp(prt[a].type, "pipe") && prt[a].type)
	{
		a++;
	}
	a++;
	return (a);
}

int	pass_pipe_red(t_red *prt)
{
	int	a;

	a = 0;
	while (ft_strcmp(prt[a].type, "pipe") && prt[a].type)
	{
		a++;
	}
	a++;
	return (a);
}

void	ft_ppcmd(t_parse *prt1, t_parse *prt2, int a, t_data *dat)
{
	int	fds[2];
	int	chil;

	pipe(fds);
	chil = fork();
	if (chil == -1)
		exit (1);
	if (chil == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		ft_output_all(prt1, dat);
		close(fds[1]);
		exit(0);
	}
	close(fds[1]);
	wait(NULL);
	dup2(fds[0], 0);
	if (a > 1)
		ft_ppcmd(prt1 + pass_pipe(prt1),
			prt2 + pass_pipe(prt2), a - 2, dat);
	else
		ft_output_all(prt2, dat);
	close(fds[0]);
}

void	ft_chiledfpi(t_parse *prt1, t_parse *prt2, t_data *dat)
{
	int		chil;

	chil = fork();
	if (chil == -1)
		exit(1);
	if (chil == 0)
	{
		ft_ppcmd(prt1, prt2, dat->commandcount - 2, dat);
		exit(0);
	}
	wait(NULL);
}
