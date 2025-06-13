/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:28:17 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/24 08:11:49 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

// int	main(void)
// {
// 	char	str[] = "Hello";
// 	char	str2[] = "Hello";
// 	size_t	n;

// 	n = 2;
// 	ft_bzero(str, n);
// 	bzero(str2, n);
// 	printf("str apres bzero : %s\n", str);
// 	printf("str2 apres bzero : %s\n", str2);
// }
