/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:24:11 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:28:58 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ifendispipe2(t_data *dat, int a)
{
	char	*temp;

	temp = NULL;
	while (dat->commandline[a - 1] == '|')
	{
		g_global.heredoc = 1;
		temp = readline("> ");
		if (temp == NULL && g_global.error == 0)
			return (1);
		if (g_global.error == 1)
		{
			free(temp);
			return (0);
		}
		dat->commandline = ft_strjoin(dat->commandline, " ");
		dat->commandline = ft_strjoin(dat->commandline, temp);
		free(temp);
		temp = ft_strtrim(dat->commandline, " ");
		free(dat->commandline);
		dat->commandline = ft_strdup(temp);
		a = ft_strlen(dat->commandline);
		if (temp)
			free(temp);
	}
	return (0);
}

int	ft_endpp(t_data *dat, int a)
{
	while (dat->commandline[a])
		a++;
	if (dat->commandline[--a] == '|')
	{
		while (--a != -1)
		{
			if (dat->commandline[a] == '<' || dat->commandline[a] == '|'
				|| dat->commandline[a] == '>')
			{
				printf("Minishell: syntax error near unexpected token `|'\n");
				dat->exitstatus = 258;
				return (1);
			}
			else if (dat->commandline[a] != ' ')
				break ;
		}
		if (ifendispipe2(dat, ft_strlen(dat->commandline)))
		{
			g_global.heredoc = 0;
			return (1);
		}
	}
	return (0);
}

int	freedoubleinput(char *temp1, char *tmp2, int stat)
{
	if (stat == 1)
	{
		free(tmp2);
		return (stat);
	}
	else if (stat == 0)
	{
		free(temp1);
		free(tmp2);
		return (stat);
	}
	return (-1);
}

int	ifdoubleinput2(t_data *dat, int a)
{
	char	*temp;
	char	*tmp2;

	temp = ft_strdup("");
	tmp2 = ft_strdup("");
	while (ft_strcmp(dat->arguments[a], temp))
	{
		if (temp)
			free(temp);
		temp = readline("> ");
		if (temp == NULL)
			return (freedoubleinput(NULL, tmp2, 1));
		if (g_global.error == 1)
			return (freedoubleinput(temp, tmp2, 0));
		if (ft_strcmp(dat->arguments[a], temp))
		{
			tmp2 = ft_strjoin(tmp2, temp);
			tmp2 = ft_strjoin(tmp2, "\n");
		}
	}
	free(dat->arguments[a]);
	dat->arguments[a] = ft_strdup(tmp2);
	free(temp);
	free(tmp2);
	return (0);
}

int	ft_dbleinp(t_data *dat)
{
	int		a;

	a = 0;
	while (dat->arguments[a])
	{
		if (!ft_strcmp(dat->arguments[a], "<<") && dat->arguments[a + 1])
		{
			g_global.heredoc = 1;
			a++;
			if (ifdoubleinput2(dat, a))
				return (1);
			if (g_global.error == 1)
				return (0);
		}
		a++;
	}
	return (0);
}
