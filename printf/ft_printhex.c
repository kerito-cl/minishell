/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:19:53 by mquero            #+#    #+#             */
/*   Updated: 2024/12/19 11:10:42 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	hexa_putchar(int divisor, char x)
{
	char	c;

	c = divisor + 55;
	if (divisor > 9 && x == 'X')
		write(2, &c, 1);
	else if (divisor > 9 && (x == 'x' || x == 'p'))
	{
		c = c + 32;
		write(2, &c, 1);
	}
	else if (divisor < 10)
		ft_putnbr_fd(divisor, 2, 1);
}

int	ft_printhex(uint64_t p, char x, int count)
{
	uint64_t	quotient;
	uint64_t	remainder;

	quotient = p;
	remainder = quotient % 16;
	if ((quotient / 16) != 0)
		count = ft_printhex(quotient / 16, x, count + 1);
	hexa_putchar(remainder, x);
	return (count);
}
