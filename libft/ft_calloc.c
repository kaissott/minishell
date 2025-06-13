/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 07:59:56 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/24 08:16:40 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((SIZE_MAX / nmemb) < size)
		return (NULL);
	s = malloc(nmemb * size);
	if (!s)
		return (NULL);
	ft_bzero(s, nmemb * size);
	return (s);
}

// int	main(void)
// {
// 	size_t	nmemb;
// 	size_t	size;
// 	size_t	total_size;
// 	size_t	i;
// 	int		*s;
// 	int		*s2;

// 	nmemb = 4;
// 	size = 4;
// 	total_size = nmemb * size;
// 	i = 0;
// 	s = ft_calloc(nmemb, size);
// 	s2 = calloc(nmemb, size);
// 	while (i < nmemb)
// 	{
// 		printf("Value : [%d]\n", s[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < nmemb)
// 	{
// 		printf("Value (vraie) : [%d]\n", s2[i]);
// 		i++;
// 	}
// 	return (0);
// }
