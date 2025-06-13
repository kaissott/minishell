/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:05:00 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/24 08:34:46 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*cdest;
	unsigned char	*csrc;

	if ((!dest && !src) || n == 0)
		return (dest);
	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	if (cdest <= csrc)
		ft_memcpy(dest, src, n);
	else if (cdest > csrc)
	{
		cdest += n - 1;
		csrc += n - 1;
		while (n--)
		{
			*cdest-- = *csrc--;
		}
	}
	return (dest);
}

// int	main(void)
// {
// 	char	dest[20] = "Hello";
// 	char	dest2[20] = "Hello";
// 	size_t	n;

// 	n = 10;
// 	ft_memmove(dest + 1, dest, n);
// 	memmove(dest2 + 1, dest2, n);
// 	printf("str apres ft_memmove : %s\n", dest);
// 	printf("str2 apres memmove : %s\n", dest2);
// }
