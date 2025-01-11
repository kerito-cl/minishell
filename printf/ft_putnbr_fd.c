/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:34:19 by mquero            #+#    #+#             */
/*   Updated: 2024/11/08 12:11:42 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fd(int64_t n, int fd, int count)
{
	int64_t	k;
	char	p;
	int64_t	rem;

	k = n;
	if (k < 0)
	{
		write(fd, "-", 1);
		k = k * -1;
		count++;
	}
	if (k < 10 && k >= 0)
	{
		p = k + '0';
		write(fd, &p, 1);
	}
	if (k > 9)
	{
		count = ft_putnbr_fd(k / 10, fd, count + 1);
		rem = (k % 10) + '0';
		write(fd, &rem, 1);
	}
	return (count);
}
