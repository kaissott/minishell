/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:58:29 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 11:52:52 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*s;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > 4294967295 / size)
		return (NULL);
	s = malloc(size * nmemb);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, nmemb * size);
	return ((void *)s);
}
