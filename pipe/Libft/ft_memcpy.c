/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 08:56:22 by karamire          #+#    #+#             */
/*   Updated: 2024/11/18 15:48:30 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = dest;
	s = src;
	i = 0;
	if ((dest == 0 && src == 0) || n == 0)
		return ((unsigned char *)dest);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return ((unsigned char *)dest);
}

/* int	main(void)
{
	// printf("%s\n", (char *)(ft_memcpy("   ", "abcdef", 3)));
	printf("%s\n", (char *)(ft_memcpy("   ", "abcdef", 3)));
} */
