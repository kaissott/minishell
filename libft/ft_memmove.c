/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 05:44:38 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 14:58:40 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == src || len == 0)
		return (dst);
	i = 0;
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		i = len - 1;
		while (i + 1 > 0)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i--;
		}
	}
	return (dst);
}

/* int	main(void)
{
	char	*src;
	char	dst1[0xF0];
	int		size;
	char	*r1;
	char	*r2;

	src = "thanks to @apellicc for this test !\r\n";
	size = strlen(src);
	r1 = memmove(dst1, src, size);
	r2 = ft_memmove(dst1, src, size);
} */

/* int    main(void)
{
	char dest[8] = "Hello";
	char dest2[8] = "Hello";
	size_t n;

	// const char    src[] = "6969";
	// const char    src2[] = "6969";
	n = 5;
	ft_memmove(dest + 1, dest, n);
	memmove(dest2 + 1, dest2, n);
	printf("str  ft_memmove : %s\n", dest);
	printf("str2  memmove : %s\n", dest2);
} */
