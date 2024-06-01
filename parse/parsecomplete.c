/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecomplete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:25:17 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:31:22 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_wordsparts(char **arg)
{
	int	a;
	int	c;

	c = 0;
	a = 0;
	while (arg[a])
	{
		if (arg[a][0] == '|' || arg[a][0] == '<' || arg[a][0] == '>')
			return (c);
		a++;
		c++;
	}
	return (c);
}

char	**ft_twdcpy(char **src)
{
	char	**dst;
	int		a;
	int		word;

	a = 0;
	if (src[0][0] && src[0][0] != '|' && src[0][0] != '<' && src[0][0] != '>')
		word = ft_wordsparts(src);
	else if ((src[0][0] == '<' || src[0][0] == '>') && src[1])
		word = 2;
	else
		word = 1;
	dst = (char **)malloc(sizeof(char *) * (word + 1));
	while (a < word)
	{
		dst[a] = ft_strdup(src[a]);
		a++;
	}
	dst[a] = NULL;
	return (dst);
}

int	ft_cntpars(t_data *dat, int a, int c, int tr)
{
	char	**str;

	str = dat->arguments;
	while (str[++a])
	{
		if ((str[a][0] == '|') || (str[a][0] == '>' || str[a][0] == '<'))
		{
			if (str[a][0] == '|')
				dat->commandcount++;
			else if (str[a + 1])
				a++;
			tr = 1;
			c++;
		}
		else if (tr == 1)
		{
			tr = 0;
			c++;
			dat->commandcount++;
		}
	}
	return (c);
}

char	*ft_lstpardef_typ(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (ft_strdup("pipe"));
	else if (!ft_strcmp(str, "<"))
		return (ft_strdup("simpleinput"));
	else if (!ft_strcmp(str, "<<"))
		return (ft_strdup("multipleinput"));
	else if (!ft_strcmp(str, ">"))
		return (ft_strdup("simpleoutput"));
	else if (!ft_strcmp(str, ">>"))
		return (ft_strdup("multipleoutput"));
	return (NULL);
}
