/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:20:12 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/16 21:34:18 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*cs;

	i = ft_strlen(s);
	cs = (char *)s;
	c = (char)c;
	if (c == '\0')
		return (&cs[i]);
	while (i >= 0)
	{
		if (cs[i] == c)
			return (&cs[i]);
		i--;
	}
	return (0);
}

// int	main(void)
// {
// 	const char	s[] = "Hello we are the world";
// 	const char	*s2;
// 	int			c;
// 	int			c2;
// 	int			c3;
// 	int			c4;

// 	c = 'w';
// 	c2 = '9';
// 	c3 = ' ';
// 	c4 = '\0';
// 	printf("c = w : %s\n", ft_strrchr(s, c));
// 	printf("c = w (vraie) : %s\n\n", strrchr(s, c));
// 	printf("c = 9 : %s\n", ft_strrchr(s, c2));
// 	printf("c = 9 (vraie) : %s\n\n", strrchr(s, c2));
// 	printf("c = esp : %s\n", ft_strrchr(s, c3));
// 	printf("c = esp (vraie) : %s\n\n", strrchr(s, c3));
// 	printf("c = \\0 : %s\n", ft_strrchr(s, c4));
// 	printf("c = \\0 (vraie) : %s\n\n", strrchr(s, c4));
// 	printf("c = \\0 && s2 = vide : %s\n", ft_strrchr(s2, c4));
// 	printf("c = \\0 && s2 = vide (vraie) : %s\n\n", strrchr(s2, c4));
// 	return (0);
// }
