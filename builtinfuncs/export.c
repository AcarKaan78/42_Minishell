/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:54:27 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:33:54 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isthere(char *strng, t_data *data)
{
	int		a;
	int		b;
	char	**tmp;

	a = 0;
	b = 0;
	while (data->envp[a])
	{
		tmp = ft_split(data->envp[a], '=');
		if (ft_strcmp(tmp[0], strng) == 0)
			return (1);
		while (tmp[b])
			free(tmp[b++]);
		free(tmp);
		b = 0;
		a++;
	}
	return (0);
}

void	sortexport(t_data *data)
{
	int		a;
	int		b;
	char	*tmp;

	a = 0;
	b = 0;
	while (data->exportp[a])
	{
		b = 0;
		while (data->exportp[b])
		{
			if (ft_strcmp(data->exportp[a], data->exportp[b]) < 0)
			{
				tmp = data->exportp[a];
				data->exportp[a] = data->exportp[b];
				data->exportp[b] = tmp;
			}
			b++;
		}
		a++;
	}
}

void	isupdate2(char *strng, int a, t_data *data)
{
	char	**tmp;
	char	**temp2;
	int		b;

	while (--a != -1)
	{
		b = 0;
		tmp = ft_split(strng, '=');
		temp2 = ft_split(data->exportp[a], '=');
		if (ft_strchr(data->exportp[a], '='))
		{
			if (ft_strcmp(tmp[0], temp2[0]) == 0)
				data->exportp = ft_rmvdbpoi(data->exportp, a);
		}
		else
			if (ft_strcmp(tmp[0], data->exportp[a]) == 0)
				data->exportp = ft_rmvdbpoi(data->exportp, a);
		while (tmp[b])
			free(tmp[b++]);
		b = 0;
		while (temp2[b])
			free(temp2[b++]);
		free(tmp);
		free(temp2);
	}
}

void	isupdate(char *strng, int a, t_data *data)
{
	if (!ft_strchr(strng, '='))
	{
		while (--a != -1)
		{
			if (ft_strcmp(data->exportp[a], strng) == 0)
				data->exportp = ft_rmvdbpoi(data->exportp, a);
		}
		return ;
	}
	isupdate2(strng, ft_cmdpnterl(data->exportp), data);
	ft_updthelpexp(data, strng);
}

void	ft_expcmd(char **strng, int a, int error, t_data *data)
{
	if (strng[1])
	{
		while (strng[++a])
		{
			if (ft_exppar(strng[a]))
			{
				if (!isthere(strng[a], data))
				{
					isupdate(strng[a], ft_cmdpnterl(data->exportp), data);
					if (ft_strchr(strng[a], '='))
						data->envp = ft_addbpoi(data->envp, strng[a]);
					data->exportp = ft_addbpoi(data->exportp, strng[a]);
				}
			}
			else
				if (error == 0 && ++error == 1)
					printf("export: not valid in this context: %s\n", strng[a]);
		}
	}
	sortexport(data);
	if (error == 0 && !strng[1])
		ft_prntexp(data);
}
