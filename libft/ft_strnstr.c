/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 06:17:50 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/18 06:35:09 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*cbig;

	i = 0;
	cbig = (char *)big;
	if (ft_strlen(little) == 0)
		return (cbig);
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] == cbig[i + j] && i + j < len)
		{
			j++;
			if (j == ft_strlen(little))
				return (&cbig[i]);
		}
		i++;
	}
	return (NULL);
}
