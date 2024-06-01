/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:27:27 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:19:08 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_of_str(char **arg)
{
	int	a;
	int	c;

	c = 0;
	a = 0;
	while (arg[a])
	{
		a++;
	}
	return (a);
}

char	**ft_towdcopy(char **src)
{
	char	**dst;
	int		a;
	int		word;

	a = 0;
	word = count_of_str(src);
	dst = (char **)malloc(sizeof(char **) * word + 1);
	while (a < word)
	{
		dst[a] = ft_strdup(src[a]);
		a++;
	}
	dst[a] = NULL;
	return (dst);
}

char	*ft_getpath(char **envo, char *str, t_data *dat)
{
	int		a;
	char	*check;

	a = 0;
	(void)envo;
	while (dat->path[a])
	{
		check = ft_strjoin2(dat->path[a], "/");
		check = ft_strjoin(check, str);
		if (access(check, F_OK) == 0)
			return (check);
		else if (access(str, X_OK) == 0)
			return (str);
		free(check);
		a++;
	}
	return (NULL);
}

void	runexecve(t_data *dat, char **str, int fds[2], int chil)
{
	char	*temp;

	if (chil == 0)
	{
		temp = ft_getpath(dat->envp, str[0], dat);
		if (execve(temp,
				str, dat->envp) == -1)
		{
			dup2(dat->fderr, 1);
			close(fds[0]);
			write(fds[1], "1", 1);
			close(fds[1]);
			if (str[0][0])
				printf("-bash: %s: command not found\n", str[0]);
			exit (0);
		}
	}
	wait(NULL);
	close(fds[1]);
	temp = malloc(3);
	read(fds[0], temp, 2);
	close(fds[0]);
	if (temp[0] == '1')
		dat->exitstatus = 127;
	free(temp);
}

void	ft_chiled(char **str, t_data *dat)
{
	int		chil;
	int		fds[2];

	g_global.execstatus = 1;
	dat->exitstatus = 0;
	pipe(fds);
	chil = fork();
	if (chil == -1)
		exit(1);
	runexecve(dat, str, fds, chil);
}
