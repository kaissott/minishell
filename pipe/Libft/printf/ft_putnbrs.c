/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:33:23 by karamire          #+#    #+#             */
/*   Updated: 2024/11/29 08:43:56 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_numsize(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	putnbr_unsigned(unsigned int n)
{
	unsigned int	size;
	char			c;

	size = ft_numsize(n);
	if (n > 9)
		putnbr_unsigned((n / 10));
	c = (n % 10) + '0';
	write(1, &c, 1);
	return (size);
}

char	*base(char c)
{
	if (c == 'X')
		return ("0123456789ABCDEF");
	else
		return ("0123456789abcdef");
}

int	putnbr_base(unsigned int n, char c)
{
	unsigned int	len;
	char			*str;
	char			p;

	str = base(c);
	len = 0;
	if (n / 16 > 0)
		len += putnbr_base((n / 16), c);
	p = str[n % 16];
	write(1, &p, 1);
	return (len + 1);
}
