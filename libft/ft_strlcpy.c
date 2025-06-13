/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:02:50 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/16 17:47:37 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

/*int	main(void)
{
	char	dest[10];
	char	src[] = "Hello";

	printf("Ma strlcpy : %d\n", ft_strlcpy(dest, src, 4));
	printf("La vraie strlcpy : %zu\n", strlcpy(dest, src, 4));
	printf("Ma strlcpy : %d\n", ft_strlcpy(dest, src, 12));
	printf("La vraie strlcpy : %zu\n", strlcpy(dest, src, 12));
	printf("Ma strlcpy : %d\n", ft_strlcpy(dest, src, 0));
	printf("La vraie strlcpy : %zu\n", strlcpy(dest, src, 0));
}*/
