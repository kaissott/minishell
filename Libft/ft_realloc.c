/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:21:15 by karamire          #+#    #+#             */
/*   Updated: 2025/05/06 11:46:41 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;

	if (!ptr)
		return (malloc(new_size));
	if (ptr && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);
	new = malloc(new_size);
	if (!new)
		return (NULL);
	if (new_size > old_size)
		ft_memcpy(new, ptr, old_size);
	else
		ft_memcpy(new, ptr, new_size);
	free(ptr);
	return (new);
}

// int	main(void)
// {
// 	char	*str;
// 	char	*str2;
// 	int		i;

// 	i = 0;
// 	str = malloc(sizeof(char) * 8);
// 	while (i < 7)
// 	{
// 		str[i] = 'a';
// 		i++;
// 	}
// 	str[i] = '\0';
// 	printf("premiere : %s\n", str);
// 	str2 = ft_realloc(str, 8, 10);
// 	printf("seconde : %s\n", str2);
// 	free(str2);
// }
