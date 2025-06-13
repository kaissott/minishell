/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:05:00 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/24 08:35:24 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*cdest;
	unsigned char	*csrc;

	if ((!dest && !src) || n == 0)
		return (dest);
	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}

// int	main(void)
// {
// 	size_t	n;
//
// char	dest[] = "Hello";
// char	dest2[] = "Hello";
// const char	src[] = "6969";
// const char	src2[] = "6969";
// char		*dest3;
// const char	*src3 = NULL;
// char		*dest4;
// const char	*src4 = NULL;
// dest3 = NULL;
// dest4 = NULL;
// n = 2;
// ft_memcpy("Hello", "6969", n);
// memcpy("Hello", "6969", n);
// ft_memcpy(dest3, src3, n);
// memcpy(dest4, src4, n);
// printf("str apres ft_memcpy : %s\n", (char *)ft_memcpy("Hello", "6969", n));
// printf("str2 apres memcpy : %s\n", (char *)memcpy("Hello", "6969", n));
// printf("str3 apres memcpy : %s\n", dest3);
// printf("str4 apres memcpy : %s\n", dest4);
// }
