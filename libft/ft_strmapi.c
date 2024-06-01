/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:13:21 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 00:59:44 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*d;
	char			*m;
	unsigned int	i;

	m = (char *)s;
	d = (char *)malloc(sizeof(char) * (ft_strlen(m) + 1));
	i = 0;
	if (!d)
		return (NULL);
	while (m[i] && m)
	{
		d[i] = f(i, (char)m[i]);
		i++;
	}
	d[i] = '\0';
	return (d);
}
