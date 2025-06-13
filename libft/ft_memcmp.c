/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 05:51:29 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/24 08:29:31 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*cs1;
	const unsigned char	*cs2;

	i = 0;
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (i < n)
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char	dest[] = "Hello";
// 	const char	src[] = "6969";
// 	const char	dest2[] = "Hello";
// 	const char	dest3[] = "\0";
// 	const char	*dest4;
// size_t		n;

// const char	*src3;
// const char	src2[] = "6969";
// const char	*src4 = NULL;
// dest4 = NULL;
// n = 2;
// printf("str apres ft_memcpy : %d\n", ft_memcmp(dest, src, n));
// printf("str2 apres memcpy : %d\n\n", memcmp(dest, src, n));
// printf("str3 apres memcpy : %d\n", ft_memcmp(dest2, src3, n));
// printf("str4 apres memcpy : %d\n\n", ft_memcmp(dest2, src3, n));
// printf("str3 apres memcpy : %d\n", ft_memcmp(dest2, src, n));
// printf("str4 apres memcpy : %d\n\n", ft_memcmp(dest2, src, n));
// printf("str3 apres memcpy : %d\n", ft_memcmp(dest3, src, n));
// printf("str4 apres memcpy : %d\n\n", ft_memcmp(dest3, src, n));
// printf("str3 apres memcpy : %d\n", ft_memcmp(dest4, src, n));
// printf("str4 apres memcpy : %d\n", ft_memcmp(dest4, src, n));
// }
