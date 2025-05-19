/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:08:56 by karamire          #+#    #+#             */
/*   Updated: 2025/02/15 16:53:02 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return (0);
	while (big[i] != '\0')
	{
		j = 0;
		while (little[j] == big[i + j])
		{
			j++;
			if (j == ft_strlen((char *)little) && big[i + j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}
