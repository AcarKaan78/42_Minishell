/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:50:26 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 00:59:14 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*d;
	int		i;
	int		j;

	i = -1;
	j = 0;
	d = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!d)
		return (0);
	else
	{
		while (s1[++i])
			d[i] = s1[i];
		while (s2[j])
		{
			d[i] = s2[j];
			j++;
			i++;
		}
		d[i] = 0;
		free(s1);
		return (d);
	}
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*d;
	int		i;
	int		j;

	i = -1;
	j = 0;
	d = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!d)
		return (0);
	else
	{
		while (s1[++i])
			d[i] = s1[i];
		while (s2[j])
		{
			d[i] = s2[j];
			j++;
			i++;
		}
		d[i] = 0;
		return (d);
	}
	return (0);
}
