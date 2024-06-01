/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:17:24 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:26:57 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getpc(void)
{
	char	*pcnm;
	int		fd[2];
	pid_t	id;
	int		byteread;
	char	**tmp;

	tmp = ft_split("scutil --get ComputerName", ' ');
	pcnm = malloc(256 * sizeof(char));
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		execve("/usr/sbin/scutil", tmp, NULL);
	}
	else
	{
		wait(NULL);
		byteread = read(fd[0], pcnm, sizeof(pcnm));
		if (byteread == -1)
			ft_error("File read error!");
		pcnm[byteread] = '\0';
		ft_frdblpoi(tmp);
	}
	return (pcnm);
}

void	ft_fndsrttxt(char *pcnm, t_data *dat)
{
	char	**pwd;
	char	*tmp;
	int		a;

	a = 0;
	tmp = getcwd(NULL, 0);
	pwd = ft_split(tmp, '/');
	free(tmp);
	dat->simplestarttext = ft_strjoin2("Miniroot - ", getenv("LOGNAME"));
	dat->simplestarttext = ft_strjoin(dat->simplestarttext, "@");
	dat->simplestarttext = ft_strjoin(dat->simplestarttext, pcnm);
	dat->starttext = ft_strjoin2(dat->simplestarttext, " ");
	tmp = getcwd(NULL, 0);
	if (ft_strcmp(tmp, getenv("HOME")) == 0)
		dat->starttext = ft_strjoin(dat->starttext, "~");
	else
		dat->starttext = ft_strjoin(dat->starttext,
				pwd[ft_cmdpnterl(pwd) - 1]);
	dat->starttext = ft_strjoin(dat->starttext, " % ");
	while (pwd[a])
		free(pwd[a++]);
	free(pwd[a]);
	free(pwd);
	free(tmp);
	free(pcnm);
}

void	printwelcome(void)
{
	printf("\033[32m/* ************************************************ */\n");
	printf("/*                                                  */\n");
	printf("/*          Welcome to our Miniroot Shell           */\n");
	printf("/*          asenel       ---       muoz             */\n");
	printf("/*                                                  */\n");
	printf("/* ************************************************ */\n\n\033[0m");
}

void	ft_initfunc(char **envp, int argc, char **argv, t_data *dat)
{
	char	*pcnm;

	if (argc > 1)
		printf("\033[31;4mMinishell: Command not found: %s\n\033[0m",
			argv[1]);
	pcnm = ft_getpc();
	ft_fndsrttxt(pcnm, dat);
	dat->path = ft_split(getenv("PATH"), ':');
	dat->envp = ft_cpyenvo(envp);
	dat->exportp = ft_cpyenvo(envp);
	dat->exportlen = ft_cmdpnterl(dat->exportp);
	g_global.error = 0;
	dat->exitstatus = 0;
	g_global.execstatus = 0;
	g_global.heredoc = 0;
	dat->commandcount = 0;
	dat->arguments = NULL;
	dat->commandline = NULL;
	dat->parts = NULL;
	dat->fderr = dup(1);
	printwelcome();
}

void	ft_error(char *a)
{
	int	i;

	i = 0;
	while (a[i])
		write(1, &a[i++], 1);
	exit(1);
}
