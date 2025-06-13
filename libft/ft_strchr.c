/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 07:43:58 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 14:48:34 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	c = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return ((char *)s + i);
	return (NULL);
}

/* int    main(void)
{
    const char    s[] = "Hello world";
    int            c;
    int            c2;
    int            c3;
    int            c4;
    const char    *s2;

    c = 'w';
    c2 = '9';
    c3 = ' ';
    c4 = '\0';
    printf("c = w : %s\n", ft_strchr(s, c));
    printf("c = w (true) : %s\n\n", strchr(s, c));
    printf("c = w : %s\n", ft_strchr(s, c2));
    printf("c = w (true) : %s\n\n", strchr(s, c2));
    printf("c = w : %s\n", ft_strchr(s, c3));
    printf("c = w (true) : %s\n\n", strchr(s, c3));
    printf("c = w : %s\n", ft_strchr(s, c4));
    printf("c = w (true) : %s\n\n", strchr(s, c4));
    printf("c = w : %s\n", ft_strchr(s2, c4));
    printf("c = w (true) : %s\n\n", strchr(s2, c4));
    return (0);
} */
