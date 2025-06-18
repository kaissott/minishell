/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:58:58 by karamire          #+#    #+#             */
/*   Updated: 2025/06/18 02:14:00 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return (big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && i + j < len)
		{
			j++;
			if (j == ft_strlen((char *)little))
				return (&big[i + j]);
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char big[] = "";
// 	char little[] = "";

// 	printf("%s\n", ft_strnstr(big, little, 17));
// }
