/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:22:10 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:28:58 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lessorgreatersign(char *str, int a, int b, t_data *dat)
{
	str[1] = '\0';
	str[2] = '\0';
	if (dat->commandline[a] == '<')
	{
		if (dat->commandline[a + 1] == '<')
		{
			str[0] = '<';
			str[1] = '<';
			b = 2;
		}
		else
			str[0] = '<';
	}
	else
	{
		if (dat->commandline[a + 1] == '>')
		{
			str[0] = '>';
			str[1] = '>';
			b = 2;
		}
		else
			str[0] = '>';
	}
	return (a + b);
}

int	elsestatus(char *str, int a, t_data *dat)
{
	int		j;

	j = 0;
	while (dat->commandline[a] && ((dat->commandline[a] != ' '
				&& dat->commandline[a] != '<'
				&& dat->commandline[a] != '>'
				&& dat->commandline[a] != '|'
				&& ft_quote(dat->commandline, a) == 0)
			|| (ft_quote(dat->commandline, a) != 0)))
	{
		str[j++] = dat->commandline[a++];
	}
	str[j] = '\0';
	return (a);
}

int	parserv2(int a, int argint, t_data *dat)
{
	int		j;
	char	*str;

	str = malloc(ft_strlen(dat->commandline) + 1);
	j = 0;
	if (dat->commandline[a] == '\"')
		a = ft_ifmorequote(str, a, &j, dat);
	else if (dat->commandline[a] == '\'')
		a = ft_squot(str, a, &j, dat);
	else if (dat->commandline[a] == '<' || dat->commandline[a] == '>')
		a = lessorgreatersign(str, a, 1, dat);
	else if (dat->commandline[a] == '|')
		a = ft_pipcont(str, a, dat);
	else
		a = elsestatus(str, a, dat);
	dat->arguments[argint] = ft_strdup(str);
	free(str);
	return (a);
}

void	continueparser(t_data *dat, int a, int argint)
{
	dat->arguments = malloc(
			ft_strlen(dat->commandline) * sizeof(char *) + 1);
	while (dat->commandline[a])
	{
		if (dat->commandline[a] == ' ')
			a++;
		else
			a = parserv2(a, argint++, dat);
	}
	dat->arguments[argint] = NULL;
	ft_erctl(dat, 0);
	if (dat->parsererrorcode == 0)
	{
		if (ft_dbleinp(dat))
			dat->parsererrorcode = 2;
		else
			g_global.heredoc = 0;
	}
}

void	ft_parsermain(t_data *dat)
{
	int		a;
	int		argint;
	char	*temp;

	temp = ft_strdup(dat->commandline);
	a = 0;
	argint = 0;
	free(dat->commandline);
	dat->commandline = ft_strtrim(temp, " ");
	free(temp);
	if (ft_endpp(dat, 0) == 1)
		dat->parsererrorcode = 3;
	else
		g_global.heredoc = 0;
	if (dat->parsererrorcode == 0 && g_global.error == 0)
		continueparser(dat, a, argint);
}
