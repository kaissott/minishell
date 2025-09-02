/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 07:43:56 by karamire          #+#    #+#             */
/*   Updated: 2025/08/28 06:58:00 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

// int	main(void)
// {
// 	char	str[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// 	int		i;

// 	i = 0;
// 	while (i < 10)
// 	{
// 		printf(" %d\n", str[i]);
// 		i++;
// 	}
// 	ft_memset(str, 'a', 10);
// 	i = 0;
// 	while (i < 10)
// 	{
// 		printf(" %d\n", str[i]);
// 		i++;
// 	}
// 	return (0);
// }
