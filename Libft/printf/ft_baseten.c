/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_baseten.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:50:03 by karamire          #+#    #+#             */
/*   Updated: 2024/11/29 08:42:59 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	basetenconv(va_list ap)
{
	int		number;
	int		size;
	char	*str;

	number = va_arg(ap, int);
	str = ft_itoa(number);
	size = printnumber(str);
	return (free(str), size);
}

int	printnumber(char *num)
{
	int	i;

	i = 0;
	while (num[i] != '\0')
	{
		write(1, &num[i], 1);
		i++;
	}
	return (i);
}
