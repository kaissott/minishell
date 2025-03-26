/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 07:44:06 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 14:59:49 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	c = (char)c;
	i = 0;
	str = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			str = ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (str);
}

// int	main(void)
// {
// 	char	str[] = "";

// 	printf("%s\n", ft_strrchr(str, 't'));
// 	printf("%s\n", ft_strrchr(str, 's'));
// 	printf("%s\n", ft_strrchr(str, '\0'));
// 	printf("%s\n", ft_strrchr(str, 'z'));
// }
