/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:15:43 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:30:29 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cntred(char **strng)
{
	int	a;
	int	c;

	c = 0;
	a = 0;
	while (strng[a] && strng[a][0] != '|')
	{
		if (strng[a][0] == '<' || strng[a][0] == '>')
			c++;
		a++;
	}
	return (c);
}

int	ft_wordpartsout_red(char **arg)
{
	int	a;
	int	c;

	c = 0;
	a = 0;
	if (arg[a][0] == '|')
		return (1);
	while (arg[a])
	{
		if (arg[a][0] == '<' || arg[a][0] == '>')
		{
			c--;
			a++;
		}
		if (arg[a][0] == '|')
			return (c);
		a++;
		c++;
	}
	return (c);
}

int	ft_redlen(t_red *red)
{
	int	a;

	a = 0;
	while (red[a].type)
	{
		a++;
	}
	return (a - 1);
}

void	ft_sub_output(t_parse *part, int a)
{
	int	fd;

	while (a + 1)
	{
		if (part->red[a].str[0] == '>' && part->red[a].str[1] == '>')
			fd = open(&(part->red[a].str[2]), O_CREAT, 0777);
		else if (part->red[a].str[0] == '>')
			fd = open(&(part->red[a].str[1]), O_CREAT, 0777);
		a--;
		close(fd);
	}
}
