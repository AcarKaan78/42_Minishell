/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublepointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:05:49 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:26:57 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_addbpoi(char **doupoi, char *ad)
{
	int		a;
	char	**returndoupoi;

	returndoupoi = malloc(sizeof(char *) * (ft_cmdpnterl(doupoi) + 2));
	a = 0;
	while (doupoi[a])
	{
		returndoupoi[a] = ft_strdup(doupoi[a]);
		free(doupoi[a]);
		a++;
	}
	free(doupoi[a]);
	returndoupoi[a] = ft_strdup(ad);
	returndoupoi[a + 1] = NULL;
	free(doupoi);
	return (returndoupoi);
}

char	**ft_rmvdbpoi(char **doupoi, int a)
{
	int		b;
	int		rdpi;
	char	**returndoupoi;

	returndoupoi = malloc(sizeof(char *) * ft_cmdpnterl(doupoi));
	rdpi = 0;
	b = 0;
	while (doupoi[b])
	{
		if (b != a)
		{
			returndoupoi[rdpi] = ft_strdup(doupoi[b]);
			rdpi++;
		}
		free(doupoi[b]);
		b++;
	}
	free(doupoi[b]);
	returndoupoi[rdpi] = NULL;
	free(doupoi);
	return (returndoupoi);
}

int	ft_exppar(char *str)
{
	int	a;

	a = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	if (str[a])
	{
		if (!ft_isalnum(str[a]) && str[a] != '_')
			return (0);
		a++;
	}
	return (1);
}

int	ft_findvnpind2(char *searchedenvp, t_data *data)
{
	int		a;
	char	**tmp;

	a = 0;
	while (data->envp[a])
	{
		tmp = ft_split(data->envp[a], '=');
		if (ft_strcmp(tmp[0], searchedenvp) == 0)
		{
			ft_frdblpoi(tmp);
			return (a);
		}
		if (tmp)
			ft_frdblpoi(tmp);
		a++;
	}
	return (-1);
}

void	ft_frdblpoi(char **str)
{
	int	a;

	a = 0;
	while (str[a])
	{
		free(str[a]);
		a++;
	}
	free(str[a]);
	free(str);
}
