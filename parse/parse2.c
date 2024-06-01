/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:23:09 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:11:35 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_prsrlngcntr(int a, t_data *dat)
{
	return (dat->commandline[a] && dat->commandline[a] != ' '
		&& dat->commandline[a] != '<' && dat->commandline[a] != '>'
		&& dat->commandline[a] != '|');
}

int	ft_pipcont(char *str, int a, t_data *dat)
{
	str[0] = dat->commandline[a];
	str[1] = '\0';
	return (++a);
}

int	ft_ifmorequote(char *str, int a, int *b, t_data *dat)
{
	while (ft_prsrlngcntr(a, dat))
	{
		if (dat->commandline[a] == '\"')
		{
			str[(*b)++] = dat->commandline[a++];
			while (dat->commandline[a] != '\"' && dat->commandline[a])
				str[(*b)++] = dat->commandline[a++];
			str[(*b)++] = dat->commandline[a++];
		}
		if (dat->commandline[a] == ' ' || dat->commandline[a] == '<'
			|| dat->commandline[a] == '>' || !dat->commandline[a]
			|| dat->commandline[a] == '|')
			break ;
		while (ft_prsrlngcntr(a, dat) && dat->commandline[a] != '\"')
		{
			if (dat->commandline[a] == '\'')
				a = ft_squot(str, a, b, dat);
			else
				str[(*b)++] = dat->commandline[a++];
		}
	}
	str[*b] = '\0';
	return (a);
}

int	ft_squot(char *str, int a, int *b, t_data *dat)
{
	while (ft_prsrlngcntr(a, dat))
	{
		if (dat->commandline[a] == '\'')
		{
			str[(*b)++] = dat->commandline[a++];
			while (dat->commandline[a] != '\'' && dat->commandline[a])
				str[(*b)++] = dat->commandline[a++];
			str[(*b)++] = dat->commandline[a++];
		}
		if (dat->commandline[a] == ' ' || dat->commandline[a] == '<'
			|| dat->commandline[a] == '>' || !dat->commandline[a]
			|| dat->commandline[a] == '|')
			break ;
		while (ft_prsrlngcntr(a, dat) && dat->commandline[a] != '\'')
		{
			if (dat->commandline[a] == '\"')
				a = ft_ifmorequote(str, a, b, dat);
			else
				str[(*b)++] = dat->commandline[a++];
		}
	}
	str[*b] = '\0';
	return (a);
}
