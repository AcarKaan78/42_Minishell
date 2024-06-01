/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_erctl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:09:00 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 11:09:44 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isredirection(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (1);
	else if (!ft_strcmp(str, ">"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (1);
	else if (!ft_strcmp(str, "<<"))
		return (1);
	else
		return (0);
}

void	errorcontrol2(t_data *dat)
{
	int	a;

	a = 0;
	if (!ft_strcmp(dat->arguments[0], "|") && dat->parsererrorcode == 0
		&& g_global.error == 0)
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		dat->exitstatus = 258;
		dat->parsererrorcode = 3;
	}
	while (dat->arguments[a] && g_global.error == 0)
		a++;
	if (isredirection(dat->arguments[a - 1]) && dat->parsererrorcode == 0
		&& g_global.error == 0)
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		dat->exitstatus = 258;
		dat->parsererrorcode = 3;
	}
}

void	ft_erctl(t_data *dat, int er)
{
	int	a;

	a = 0;
	while (dat->arguments[a] && dat->arguments[a + 1]
		&& dat->parsererrorcode == 0 && g_global.error == 0)
	{
		if (!ft_strcmp(dat->arguments[a], "|")
			&& !ft_strcmp(dat->arguments[a + 1], "|"))
			er = 1;
		else if (isredirection(dat->arguments[a])
			&& isredirection(dat->arguments[a + 1]))
			er = 1;
		else if (isredirection(dat->arguments[a])
			&& !ft_strcmp(dat->arguments[a + 1], "|"))
			er = 1;
		if (er == 1)
		{
			printf("Minishell: syntax error near unexpected token `%s'\n",
				dat->arguments[a + 1]);
			dat->exitstatus = 258;
			dat->parsererrorcode = 3;
		}
		a++;
	}
	errorcontrol2(dat);
}
