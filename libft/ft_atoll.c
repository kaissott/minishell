/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 01:14:36 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/21 02:40:59 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdio.h>

static int	ft_accumulate_digits(const char *str, long long *result, int sign,
		int *error)
{
	int					digit;
	unsigned long long	limit;

	if (sign == 1)
		limit = LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MAX + 1;
	while (*str && ft_isdigit(*str))
	{
		digit = *str - '0';
		if ((unsigned long long)(*result) > (limit - digit) / 10)
		{
			*error = -1;
			return (0);
		}
		*result = *result * 10 + digit;
		str++;
	}
	return (1);
}

long long	ft_atoll(const char *str, int *error)
{
	int			sign;
	long long	result;

	*error = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!ft_accumulate_digits(str, &result, sign, error))
		return (-1);
	return (result * sign);
}
