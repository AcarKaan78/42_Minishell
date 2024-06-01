/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublepointer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:07:26 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:33:54 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmdpnterl(char **str)
{
	int	a;

	a = 0;
	while (str[a])
		a++;
	return (a);
}

char	**ft_cpyenvo(char **envo)
{
	char	**copiedenvo;
	int		a;

	a = 0;
	while (envo[a])
		a++;
	copiedenvo = malloc(sizeof(char *) * (a + 1));
	a = -1;
	while (envo[++a])
		copiedenvo[a] = ft_strdup(envo[a]);
	copiedenvo[a] = NULL;
	return (copiedenvo);
}

void	ft_prntexp(t_data *dat)
{
	int	a;
	int	b;
	int	stat;

	a = -1;
	b = 0;
	stat = 0;
	while (dat->exportp[++a])
	{
		while (dat->exportp[a][b])
		{
			printf("%c", dat->exportp[a][b]);
			if (stat == 0 && dat->exportp[a][b] == '=')
			{
				stat = 1;
				printf("\"");
			}
			b++;
		}
		if (ft_strchr(dat->exportp[a], '='))
			printf("\"");
		printf("\n");
		stat = 0;
		b = 0;
	}
}

void	ft_updthelpexp(t_data *dat, char *str)
{
	int		a;
	int		b;
	char	**tmp;
	char	**tmp2;

	b = 0;
	a = ft_cmdpnterl(dat->envp);
	while (--a != -1)
	{
		b = 0;
		tmp = ft_split(dat->envp[a], '=');
		tmp2 = ft_split(str, '=');
		if (ft_strcmp(tmp2[0], tmp[0]) == 0)
			dat->envp = ft_rmvdbpoi(dat->envp, a);
		while (tmp[b])
			free(tmp[b++]);
		free(tmp);
		b = 0;
		while (tmp2[b])
			free(tmp2[b++]);
		free(tmp2);
	}
}
