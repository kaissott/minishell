/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 07:28:18 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 14:57:29 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*int	main(void)
{
	printf("true %d\n", ft_isdigit('0'));
	printf("true %d\n", ft_isdigit('5'));
	printf("true %d\n", ft_isdigit('9'));
	printf("false %d\n", ft_isdigit('a'));
	printf("false %d\n", ft_isdigit('/'));
	printf("false %d\n", ft_isdigit(' '));
}*/
