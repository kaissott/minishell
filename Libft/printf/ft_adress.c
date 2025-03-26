/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adress.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:41:57 by karamire          #+#    #+#             */
/*   Updated: 2024/11/29 08:44:12 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_adress_base(void *ptr)
{
	unsigned long	adress;
	int				len;
	char			*str;

	adress = (unsigned long)ptr;
	if (ptr == 0)
		return (write(1, "0", 1));
	str = "0123456789abcdef";
	len = 0;
	if (adress / 16 > 0)
		len += ft_adress_base((void *)(adress / 16));
	write(1, &str[adress % 16], 1);
	return (len + 1);
}
