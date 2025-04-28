/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:05:00 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/16 20:00:32 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cs;

	cs = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		cs[i] = c;
		i++;
	}
	return (s);
}

// int	main(void)
// {
// 	char	str[] = "Hello";
// 	char	str2[] = "Hello";
// 	int		c;
// 	size_t	n;

// 	c = 69;
// 	n = 5;
// 	ft_memset(str, c, n);
// 	memset(str2, c, n);
// 	printf("str apres ft_memset : %s\n", str);
// 	printf("str2 apres memset : %s\n", str2);
// }
