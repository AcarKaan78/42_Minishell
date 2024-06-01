/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:16:11 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 00:59:38 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	x;
	char			*dest;
	char			*source;

	x = ft_strlen(src);
	i = 0;
	dest = (char *)dst;
	source = (char *)src;
	if (dstsize != 0)
	{
		while (source [i] != '\0' && i < dstsize - 1)
		{
			dest[i] = source[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (x);
}
