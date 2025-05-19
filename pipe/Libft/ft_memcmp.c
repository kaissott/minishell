/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:18:15 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 14:58:30 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*compared;
	const unsigned char	*comparator;
	size_t				i;

	compared = s1;
	comparator = s2;
	i = 0;
	while (n != 0)
	{
		if (compared[i] != comparator[i])
			return (compared[i] - comparator[i]);
		i++;
		n--;
	}
	return (0);
}

// int	main(void)
// {
// 	int	s1[] = {1, 2, 3, 4, 5};
// 	int	s2[] = {1, 2, 3, 4, 16};

// 	printf("+  %d\n", memcmp(s1, s2, sizeof(int) * 5));
// 	printf("+  %d\n", memcmp(s2, s1, sizeof(int) * 5));
// 	printf("=  %d\n", memcmp(s1, s2, sizeof(int) * 4));
// 	printf("+  %d\n", ft_memcmp(s1, s2, sizeof(int) * 5));
// 	printf("+  %d\n", ft_memcmp(s2, s1, sizeof(int) * 5));
// 	printf("=  %d\n", ft_memcmp(s1, s2, sizeof(int) * 4));
// }
