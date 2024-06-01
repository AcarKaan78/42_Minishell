/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:56:41 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:20:46 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unsetcmd(char **str, t_data *data)
{
	int	a;

	a = 0;
	if (ft_cmdpnterl(str) == 1)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	while (str[++a])
	{
		if (ft_exppar(str[a]))
		{
			if (ft_fndindvp(str[a], ft_strlen(str[a]), data) != -1)
			{
				data->envp = ft_rmvdbpoi(data->envp,
						ft_fndindvp(str[a], ft_strlen(str[a]), data));
			}
			if (ft_fndexpind(str[a], ft_strlen(str[a]), data) != -1)
				data->exportp = ft_rmvdbpoi(data->exportp,
						ft_fndexpind(str[a], ft_strlen(str[a]), data));
		}
		else
			printf("bash: unset: `%s': not a valid identifier\n", str[a]);
	}
}
