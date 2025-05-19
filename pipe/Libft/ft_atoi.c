/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:38:32 by karamire          #+#    #+#             */
/*   Updated: 2025/02/17 17:24:24 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_intchecker(long result, long sign, int i, char *str)
{
	if (result > (LONG_MAX - ((str[i] - 48)) / 10))
	{
		if (sign == 1)
			return (-1);
		else
			return (0);
	}
	result = result + (str[i] - 48);
	if (str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		result = result * 10;
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		result = ft_intchecker(result, sign, i, (char *)str);
		i++;
	}
	return (result * sign);
}
