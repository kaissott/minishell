/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:20:41 by ludebion          #+#    #+#             */
/*   Updated: 2025/03/26 05:45:39 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	s1[] = "Hello";
// 	char	s2[] = "Hel";
// 	char	same[] = "Hello";
// 	char	inf[] = "hello";
// 	char	sup[] = "HEllo";
// 	char	diff[] = "Hilloo";
// 	char	strinf[] = "Hello";

// 	printf("Ma strcmp (identiques) : %d\n", ft_strncmp(s1, same, 2));
// 	printf("La strcmp (identiques) : %d\n", strncmp(s1, same, 2));
// 	printf("Ma strcmp (inf) : %d\n", ft_strncmp(s1, inf, 2));
// 	printf("La strcmp (inf) : %d\n", strncmp(s1, inf, 2));
// 	printf("Ma strcmp (sup) : %d\n", ft_strncmp(s1, sup, 2));
// 	printf("La strcmp (sup) : %d\n", strncmp(s1, sup, 2));
// 	printf("Ma strcmp (diff) : %d\n", ft_strncmp(s1, diff, 2));
// 	printf("La strcmp (diff) : %d\n", strncmp(s1, diff, 2));
// 	printf("Ma strcmp (diff) mais n = 0 : %d\n", ft_strncmp(s1, diff, 0));
// 	printf("La strcmp (diff) mais n = 0 : %d\n", strncmp(s1, diff, 0));
// 	printf("Ma strcmp (s2 len sup) : %d\n", ft_strncmp(s2, strinf, 10));
// 	printf("La strcmp (s2 len sup) : %d\n", strncmp(s2, strinf, 10));
// }
