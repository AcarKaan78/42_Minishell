/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:51:10 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:26:16 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echoflgcnt(char *strng)
{
	int	a;

	a = 0;
	if (strng[a] == '-')
	{
		while (strng[++a])
		{
			if (strng[a] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

void	ft_prnttw_str(char **strng, int flagcontrol)
{
	int	a;

	a = 0;
	while (strng[a])
	{
		printf("%s", strng[a]);
		if (strng[a + 1])
			printf(" ");
		a++;
		if (!strng[a] && flagcontrol == 0)
			printf("\n");
	}
}

void	ft_echocmd(char **strng)
{
	if (strng[1])
	{
		if (ft_echoflgcnt(strng[1]) == 1)
			ft_prnttw_str(&strng[2], 1);
		else
			ft_prnttw_str(&strng[1], 0);
	}
	else
		printf("\n");
}
