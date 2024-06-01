/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:10:04 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:34:04 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dscnmmkng(char **strng, t_data *dat)
{
	if (ft_strcmp(strng[0], "cd") == 0)
		ft_cd(strng, dat);
	else if (ft_strcmp(strng[0], "echo") == 0)
		ft_echocmd(strng);
	else if (ft_strcmp(strng[0], "env") == 0)
		ft_envcmd(dat);
	else if (ft_strcmp(strng[0], "export") == 0)
		ft_expcmd(strng, 0, 0, dat);
	else if (ft_strcmp(strng[0], "pwd") == 0)
		ft_pwd(dat);
	else if (ft_strcmp(strng[0], "unset") == 0)
		ft_unsetcmd(strng, dat);
	else if (ft_strcmp(strng[0], "exit") == 0)
		ft_exitcmd(dat);
	else
		ft_chiled(strng, dat);
}

void	ft_cmdfndpipe(t_data *dat)
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

void	ft_addquo(char **arguments, int a)
{
	char	*temp;

	temp = ft_strjoin2("\"", arguments[a]);
	free(arguments[a]);
	arguments[a] = ft_strjoin(temp, "\"");
}

void	ft_adstrhelp2(t_data *dat, char *firststr, int argi, int startindex)
{
	int	a;

	a = -1;
	while (++a < startindex)
		firststr[a] = dat->arguments[argi][a];
	firststr[a] = 0;
}

void	ft_addstrhelp3(t_data *dat, char *thirdstr, int argi, int endindex)
{
	int	a;

	a = 0;
	while (dat->arguments[argi][endindex])
		thirdstr[a++] = dat->arguments[argi][endindex++];
	thirdstr[a] = 0;
}
