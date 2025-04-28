/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:28:30 by ludebion          #+#    #+#             */
/*   Updated: 2025/03/25 23:29:21 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_int_overflow(int n, int digit, int sign)
{
	if (sign > 0)
	{
		if (n > (INT_MAX - digit) / 10)
			return (0);
	}
	else if (-n < (INT_MIN + digit) / 10)
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	sign;
	int	digit;

	i = 0;
	n = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		digit = nptr[i] - '0';
		if (!check_int_overflow(n, digit, sign))
			return (0);
		n = n * 10 + digit;
		i++;
	}
	return (sign * n);
}
