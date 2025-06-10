/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:58:58 by karamire          #+#    #+#             */
/*   Updated: 2025/06/10 19:38:36 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return (-1);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && i + j < len)
		{
			j++;
			if (j == ft_strlen((char *)little))
				return (1);
		}
		i++;
	}
	return (-1);
}

// int	main(void)
// {
// 	char big[] = "";
// 	char little[] = "";

// 	printf("%s\n", ft_strnstr(big, little, 17));
// }
