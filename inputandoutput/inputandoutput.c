/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputandoutput.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:20:01 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:23:59 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_smpincmd(int a, t_data *dat)
{
	int	fd;

	fd = open(dat->parts[a + 1].str[0], O_RDWR);
	if (fd == -1)
	{
		printf("%s:\033[0m \033[31;4m%s: No such file or directory\033[0m\n",
			dat->simplestarttext, dat->parts[a + 1].str[0]);
	}
	else
		close(fd);
	return (NULL);
}

char	*ft_smpoutcmd(int a, t_data *dat)
{
	int	fd;

	fd = open(dat->parts[a + 1].str[0], O_RDWR | O_CREAT | O_TRUNC, 0777);
	close(fd);
	return (NULL);
}
