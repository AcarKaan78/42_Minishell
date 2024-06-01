/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:23:06 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 00:59:08 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*d;
	char	*m;

	i = 0;
	m = (char *)s1;
	d = (char *)malloc(sizeof(char) * ft_strlen(m) + 1);
	if (!d)
		return (0);
	while (m[i])
	{
		d[i] = m[i];
		i++;
	}
	d[i] = 0;
	return (d);
}
