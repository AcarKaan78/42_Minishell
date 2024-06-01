/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotesfunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:14:34 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:26:00 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_quoterr(t_data *dat)
{
	char	*tmp;

	if (ft_quote(dat->commandline,
			ft_strlen(dat->commandline)) != 0)
	{
		tmp = ft_strtrim(dat->starttext, "\033[320m");
		printf("\033[31;4m%sQuote Error!\n\033[0m", tmp);
		free(dat->commandline);
		free(tmp);
		dat->commandline = NULL;
		dat->errorstatus = 1;
		dat->exitstatus = 1;
	}
}

int	ft_quote(char *line, int control)
{
	int	a;
	int	sgn;

	sgn = 0;
	a = 0;
	while (line[a] && a <= control)
	{
		if (line[a] == '\'')
		{
			if (sgn == 0)
				sgn = 1;
			else if (sgn == 1)
				sgn = 0;
		}
		else if (line[a] == '\"')
		{
			if (sgn == 0)
				sgn = 2;
			else if (sgn == 2)
				sgn = 0;
		}
		a++;
	}
	return (sgn);
}

char	*ft_rmvquo2(char *str)
{
	int		a;
	int		stat;
	char	*rtrnvalue;
	int		j;

	rtrnvalue = malloc(ft_strlen(str) + 1);
	stat = 0;
	j = 0;
	a = -1;
	while (str[++a])
	{
		if (str[a] == '\"' && stat == 1)
			stat = 0;
		else if (str[a] == '\"' && stat == 0)
			stat = 1;
		else if (str[a] == '\'' && stat == 2)
			stat = 0;
		else if (str[a] == '\'' && stat == 0)
			stat = 2;
		else
			rtrnvalue[j++] = str[a];
	}
	rtrnvalue[j] = 0;
	return (rtrnvalue);
}

void	ft_rmvquo(t_data *dat)
{
	int		a;
	int		j;
	char	*tmp;
	char	**rtrnvalue;

	a = 0;
	j = 0;
	rtrnvalue = malloc(sizeof(char *)
			* (ft_cmdpnterl(dat->arguments) + 1));
	while (dat->arguments[a])
	{
		tmp = dat->arguments[a];
		rtrnvalue[a] = ft_rmvquo2(tmp);
		free(tmp);
		a++;
	}
	free(dat->arguments[a]);
	free(dat->arguments);
	rtrnvalue[a] = NULL;
	dat->arguments = rtrnvalue;
}
