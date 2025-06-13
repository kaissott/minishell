/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:08:56 by karamire          #+#    #+#             */
/*   Updated: 2025/05/12 23:20:58 by kaissramire      ###   ########.fr       */
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
			if (j == ft_strlen((char *)little))
				return (1);
		}
		i++;
	}
	return (0);
}
