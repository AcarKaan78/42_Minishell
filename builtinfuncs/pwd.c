/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:55:48 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:26:57 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_data *data)
{
	char	**tmp;
	int		a;

	a = 0;
	tmp = ft_split(data->envp[ft_fndindvp("PWD=", 4, data)], '=');
	printf("%s\n", tmp[1]);
	ft_frdblpoi(tmp);
}
