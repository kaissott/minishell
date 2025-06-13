/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 07:43:51 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 15:00:20 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;

	c = (unsigned char)c;
	ptr = s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == c)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}
