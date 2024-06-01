/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonem <amonem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:20:47 by gotunc            #+#    #+#             */
/*   Updated: 2023/11/22 00:57:39 by amonem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	a;

	a = n;
	if (a == -2147483648)
		write(fd, "-2147483648", 11);
	else if (a < 0)
	{
		write(fd, "-", 1);
		a *= -1;
		ft_putnbr_fd(a, fd);
	}
	else if (a > 9)
	{
		ft_putnbr_fd(a / 10, fd);
		ft_putnbr_fd(a % 10, fd);
	}
	else if (a >= 0 && a < 10)
	{
		a += 48;
		write(fd, &a, 1);
	}
}
