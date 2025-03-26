/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 07:38:23 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 14:57:29 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/*int main(void)
{
	printf("true %d\n", ft_isalpha(77));
	printf("true %d\n", ft_isalpha(122));
	printf("true %d\n", ft_isalpha(67));
	printf("false %d\n", ft_isalpha(62));
	printf("false %d\n", ft_isalpha(126));
	printf("false %d\n", ft_isalpha(11));
}*/
