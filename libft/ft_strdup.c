/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:09:51 by ludebion          #+#    #+#             */
/*   Updated: 2025/05/20 04:28:17 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s);
	if (!len)
		return (NULL);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	str = ft_strcpy(str, s);
	return (str);
}

// int	main(void)
// {
// 	char	str[] = "Hello";

// 	printf("Ma strdup : %s\n", ft_strdup(str));
// 	printf("La strdup : %s\n", strdup(NULL));
// }
