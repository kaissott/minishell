/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:21:15 by karamire          #+#    #+#             */
/*   Updated: 2025/05/03 09:50:45 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_realloc(void *ptr, int old_size, int new_size)
{
	void	*new;

	if (!ptr)
		return (NULL);
	if (new_size == 0)
		return (NULL);
	new = malloc(new_size);
	if (!new)
		return (NULL);
	if (new_size > old_size)
		ft_memcpy(new, ptr, old_size);
	if (new_size < old_size)
		ft_memcpy(new, ptr, new_size);
	return (new);
}
int	main(void)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * 8);
	while (i < 8)
	{
		str[i] = 'a';
		i++;
	}
	printf("Avant realloc : %s\n", str);
	ft_realloc(str, 8, 6);
	// printf("Apres realloc : %s\n", str);
}
