/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:52:04 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:17:39 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isprintableenv(char **strng)
{
	int	a;

	a = 1;
	while (strng[a])
	{
		if (ft_strchr(strng[a], '=') == NULL)
			return (0);
		a++;
	}
	return (1);
}

void	ft_envcmd(t_data *data)
{
	int	a;

	a = 0;
	while (a < ft_cmdpnterl(data->envp))
		printf("%s\n", data->envp[a++]);
}
