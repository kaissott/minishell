/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 07:43:36 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 14:57:00 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// int	main(void)
// {
// 	printf("true %d\n", ft_isalnum('0'));
// 	printf("true %d\n", ft_isalnum('Z'));
// 	printf("true %d\n", ft_isalnum('k'));
// 	printf("false %d\n", ft_isalnum('.'));
// 	printf("false %d\n", ft_isalnum(']'));
// 	printf("false %d\n", ft_isalnum('-'));
// }
