/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:00:11 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:34:04 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dollarfill(t_data *dat, int m, int startint, int endint)
{
	char	*tmp;
	int		a;
	int		b;

	a = startint;
	b = 0;
	tmp = malloc(sizeof(char) * (endint - startint + 1));
	while (a < endint)
	{
		tmp[b++] = dat->arguments[m][a++];
	}
	tmp[b] = '\0';
	return (tmp);
}

char	*addstringhelper(char *firststrng, char *tmp, char *thirdstrng)
{
	char	*tmp2;

	tmp2 = ft_strjoin(firststrng, tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, thirdstrng);
	free(thirdstrng);
	return (tmp);
}

char	*addstring(int argint, int startint, int endint, t_data *dat)
{
	char	*firststrng;
	char	*tmp;
	char	*addstrng;
	char	*thirdstrng;
	char	**temp3;

	addstrng = dollarfill(dat, argint, startint, endint);
	firststrng = malloc(sizeof(char) * (startint + 1));
	thirdstrng = malloc((ft_strlen(dat->arguments[argint]) - endint + 1));
	ft_adstrhelp2(dat, firststrng, argint, startint);
	ft_addstrhelp3(dat, thirdstrng, argint, endint);
	if (ft_findvnpind2(addstrng + 1, dat) != -1)
	{
		temp3 = ft_split(dat->envp[ft_findvnpind2(addstrng + 1, dat)], '=');
		tmp = ft_strdup(temp3[1]);
		ft_frdblpoi(temp3);
	}
	else if (!ft_strcmp(addstrng, "$?"))
		tmp = ft_itoa(dat->exitstatus);
	else
		tmp = ft_strdup("\0");
	free(dat->arguments[argint]);
	free(addstrng);
	return (addstringhelper(firststrng, tmp, thirdstrng));
}

void	transformdollar2(t_data *dat, int a, int m, int b)
{
	while (dat->arguments[a][++b])
	{
		if (dat->arguments[a][b] == '$')
		{
			m = b + 1;
			if (dat->arguments[a][m] == '?')
				m++;
			else if (ft_isdigit(dat->arguments[a][m])
				|| (!ft_isalnum(dat->arguments[a][m])
					&& dat->arguments[a][m] != ' '))
				m++;
			else
			{
				while (!ft_isdigit(dat->arguments[a][b + 1])
						&& (ft_isalnum(dat->arguments[a][m])
							|| dat->arguments[a][m] == '_')
						&& dat->arguments[a][m])
					m++;
			}
			dat->arguments[a] = addstring(a,
					b, m, dat);
			b = m;
		}
	}
}

void	ft_trndol(t_data *dat, int quote)
{
	int		a;
	int		b;
	char	*tmp;

	a = -1;
	b = 0;
	while (dat->arguments[++a])
	{
		if (dat->arguments[a][0] != '\''
			&& ft_strchr(dat->arguments[a], '$'))
		{
			if (dat->arguments[a][0] == '\"'
				&& dat->arguments[a]
				[ft_strlen(dat->arguments[a]) - 1] == '\"')
			{
				tmp = ft_strtrim(dat->arguments[a], "\"");
				free(dat->arguments[a]);
				dat->arguments[a] = tmp;
				quote = 1;
			}
			transformdollar2(dat, a, 0, -1);
			if (quote == 1)
				ft_addquo(dat->arguments, a);
		}
	}
}
