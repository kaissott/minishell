/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 07:44:10 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 15:00:04 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}

/*int	main(void)
{
	printf(" %d\n", ft_toupper('A'));
	printf(" %d\n", ft_toupper('Y'));
	printf(" %d\n", ft_toupper('r'));
	printf(" %d\n", ft_toupper('t'));
}*/
