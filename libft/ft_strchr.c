/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:11 by ludebion          #+#    #+#             */
/*   Updated: 2025/03/25 20:02:08 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*cs;

	i = 0;
	cs = (char *)s;
	c = (char)c;
	while (cs[i])
	{
		if (cs[i] == c)
			return (&cs[i]);
		i++;
	}
	if (c == '\0')
		return (&cs[i]);
	return (0);
}

// int	main(void)
// {
// 	const char	s[] = "Hello world";
// 	const char	*s2;
// 	const char	s3[] = "\0";
// 	int			c;
// 	int			c2;
// 	int			c3;
// 	int			c4;

// 	c = 'w';
// 	c2 = '9';
// 	c3 = ' ';
// 	c4 = '\0';
// 	printf("c = w : %s\n", ft_strchr(s, c));
// 	printf("c = w (vraie) : %s\n\n", strchr(s, c));
// 	printf("c = 9 : %s\n", ft_strchr(s, c2));
// 	printf("c = 9 (vraie) : %s\n\n", strchr(s, c2));
// 	printf("c = esp : %s\n", ft_strchr(s, c3));
// 	printf("c = esp (vraie) : %s\n\n", strchr(s, c3));
// 	printf("c = \\0 : %s\n", ft_strchr(s, c4));
// 	printf("c = \\0 (vraie) : %s\n\n", strchr(s, c4));
// 	printf("c = esp s3 = \\0 : %s\n", ft_strchr(s3, c3));
// 	printf("c = esp s3 = \\0 (vraie) : %s\n\n", strchr(s3, c3));
// 	printf("c = \\0 s2 = vide : %s\n", ft_strchr(s2, c4));
// 	printf("c = \\0 s2 = vide (vraie) : %s\n\n", strchr(s2, c4));
// 	return (0);
// }
