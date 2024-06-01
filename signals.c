/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:33:44 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:30:37 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sndquit(int sig)
{
	(void)sig;
	rl_redisplay();
	return ;
}

void	ft_ifsigint(int sig)
{
	if (g_global.heredoc)
	{
		(void)sig;
		g_global.error = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\033[A", 3);
		return ;
	}
	else
	{
		if (g_global.execstatus)
		{
			ft_putstr_fd("\n", 2);
			printf("\033[1A");
			rl_on_new_line();
			rl_replace_line("", 0);
			return ;
		}
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\033[A", 4);
		rl_replace_line("", 0);
	}
}

void	ft_ifsend(t_data *dat)
{
	printf("\033[K");
	printf("\033[1A");
	printf("%sexit                                        \n", dat->starttext);
	printf("\t\033[32m   _____\n");
	printf("\t  /     \\\n");
	printf("\t /       \\\n");
	printf("\t|   .   . |\n");
	printf("\t|  ´   ´  |\n");
	printf("\t|   ___   |\n");
	printf("\t|  /   \\  |\n");
	printf("\t \\       /\n");
	printf("\t  \\_____/\n\n\033[0m");
	exit(0);
}

void	del_ctr(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_p) != 0)
		perror("Minishell: tcsetattr");
}
