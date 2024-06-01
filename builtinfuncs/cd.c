/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:49:18 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:26:57 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	makepwd(char *oldpwd, char *newpwd, t_data *dat)
{
	int		oldpwdind;
	int		curpwdindex;
	char	**newstartext;

	oldpwdind = ft_fndindvp("OLDPWD=", 7, dat);
	curpwdindex = ft_fndindvp("PWD=", 4, dat);
	free(dat->envp[oldpwdind]);
	free(dat->envp[curpwdindex]);
	dat->envp[oldpwdind] = ft_strjoin2("OLDPWD=", oldpwd);
	dat->envp[curpwdindex] = ft_strjoin2("PWD=", newpwd);
	free(dat->starttext);
	if (ft_strcmp(newpwd, getenv("HOME")) == 0)
		dat->starttext = ft_strjoin2(dat->simplestarttext, " ~ ");
	else
	{
		newstartext = ft_split(dat->envp[curpwdindex], '/');
		dat->starttext = ft_strjoin2(dat->simplestarttext, " ");
		dat->starttext = ft_strjoin(dat->starttext,
				newstartext[ft_cmdpnterl(newstartext) - 1]);
		dat->starttext = ft_strjoin(dat->starttext, " % ");
		ft_frdblpoi(newstartext);
	}
	free(newpwd);
	free(oldpwd);
}

void	ft_cd(char **str, t_data *dat)
{
	int		a;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	a = ft_cmdpnterl(str);
	if (a == 1 || (a == 2 && ft_strcmp(str[1], "~") == 0))
	{
		chdir(getenv("HOME"));
		makepwd(pwd, getcwd(NULL, 0), dat);
	}
	else
	{
		if (chdir(str[1]))
		{
			free(pwd);
			perror(str[1]);
		}
		else
			makepwd(pwd, getcwd(NULL, 0), dat);
	}
}
