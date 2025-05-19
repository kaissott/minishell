/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:01:41 by karamire          #+#    #+#             */
/*   Updated: 2025/02/27 23:20:10 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(ft_strlen(s) - 4);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 5;
	while (s[j] != '\0')
	{
		str[i] = s[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

// int	main(void)
// {
// 	char str[] = "hey";
// 	ft_strdup(str);
// }
