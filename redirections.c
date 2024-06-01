/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:32:31 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:25:24 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_odd_right_redirection(char *strng, t_data *dat, t_parse *prt)
{
	int	fd;
	int	chil;

	fd = open(strng, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	chil = fork();
	if (chil == -1)
		exit(1);
	if (chil == 0)
	{
		dup2(fd, 1);
		ft_input_all(prt, dat);
		close(fd);
		exit(0);
	}
	wait(NULL);
}

void	ft_odd_left_redirection(char *strng, t_data *dat, t_parse *prt)
{
	int	fd;
	int	chil;

	fd = open(strng, O_RDWR, 0777);
	chil = fork();
	if (chil == -1)
		exit(1);
	if (chil == 0)
	{
		dup2(fd, 0);
		ft_dscnmmkng(prt[0].str, dat);
		exit(0);
	}
	wait(NULL);
}

void	ft_multiple_right_redirection(char *strng, t_data *dat, t_parse *prt)
{
	int	fd;
	int	chil;

	fd = open(strng, O_CREAT | O_WRONLY | O_APPEND, 0777);
	chil = fork();
	if (chil == -1)
		exit(1);
	if (chil == 0)
	{
		dup2(fd, 1);
		ft_input_all(prt, dat);
		close(fd);
		exit(0);
	}
	wait(NULL);
}

void	ft_multiple_left_redirection(char *strng, t_data *dat, t_parse *prt)
{
	int	fds[2];
	int	chil;

	pipe(fds);
	write(fds[1], strng, ft_strlen(strng));
	chil = fork();
	if (chil == -1)
		exit(1);
	if (chil == 0)
	{
		close(fds[1]);
		dup2(fds[0], 0);
		ft_dscnmmkng(prt[0].str, dat);
		close(fds[0]);
		exit(0);
	}
	close(fds[1]);
	close(fds[0]);
	wait(NULL);
}
