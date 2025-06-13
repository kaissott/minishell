/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:56:53 by ludebion          #+#    #+#             */
/*   Updated: 2025/02/22 19:14:50 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = 0;
	src_len = ft_strlen(src);
	while (dest[dest_len] && dest_len < dstsize)
		dest_len++;
	if (dstsize <= dest_len)
		return (dstsize + src_len);
	while (src[i] && (dest_len + i) < dstsize - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

/*int   main(void)
{
		char    dest[40] = "Hello";
		char    src[] = "comment tu vas?";
	char    dest2[40] = "Hello";
	char	dest3[40] = "Hello";
	char    dest4[40] = "Hello";
	char    dest5[40] = "Hello";
	char    dest6[40] = "Hello";
	char    dest7[5] = "Hello";
		char    dest8[5] = "Hello";

		printf("Ma strlcat : %d\n", ft_strlcat(dest, src, 40));
		printf("La strlcat : %zu\n", strlcat(dest2, src, 40));
	printf("Ma strlcat (buffer null) : %d\n", ft_strlcat(dest3, src, 0));
		printf("La strlcat (buffer null) : %zu\n", strlcat(dest4, src, 0));
	printf("Ma strlcat (mauvais buffer) : %d\n", ft_strlcat(dest5, src, 4));
		printf("La strlcat (mauvais buffer) : %zu\n", strlcat(dest6, src, 4));
	printf("Ma strlcat (dest trop petite) : %d\n", ft_strlcat(dest7, src, 5));
		printf("La strlcat (dest trop petite) : %zu\n", strlcat(dest8, src, 5));
}*/
