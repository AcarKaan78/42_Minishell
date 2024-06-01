/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:45:45 by ahsezer           #+#    #+#             */
/*   Updated: 2023/11/22 00:57:45 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	part_counter(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static void	strs(char **str_list, char *s, char c)
{
	char		**tab_ptr;
	char		*temp;

	tab_ptr = str_list;
	while (*s)
	{
		while (*s == c)
			s++;
		temp = s;
		while (*temp && *temp != c)
			temp++;
		if (*temp == c || temp > s)
		{
			*tab_ptr = ft_substr(s, 0, temp - s);
			s = temp;
			tab_ptr++;
		}
	}
	*tab_ptr = NULL;
}

char	**ft_split(char *s, char c)
{
	char	**str_list;
	int		len;

	if (!s)
		return (NULL);
	len = part_counter(s, c);
	str_list = (char **) malloc(sizeof(char *) * (len + 1));
	if (!str_list)
		return (NULL);
	strs(str_list, s, c);
	return (str_list);
}
