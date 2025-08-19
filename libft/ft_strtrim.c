/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:33:35 by karamire          #+#    #+#             */
/*   Updated: 2025/08/19 17:52:01 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_starttrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
				break ;
			j++;
		}
		if (set[j] == '\0') // Character not found in set
			break ;
		i++;
	}
	return (i);
}

static int	ft_endtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (0);
	i = ft_strlen(s1);
	if (i == 0)
		return (0);
	i--;
	while (i > 0)
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
				break ;
			j++;
		}
		if (set[j] == '\0') // Character not found in set
			break ;
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t start;
	size_t end;
	size_t len;
	size_t k;
	char *newstr;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));

	start = ft_starttrim(s1, set);
	end = ft_endtrim(s1, set);

	if (start >= ft_strlen(s1))
	{
		newstr = malloc(1);
		if (newstr)
			newstr[0] = '\0';
		return (newstr);
	}

	len = end - start + 1;
	newstr = malloc(len + 1);
	if (!newstr)
		return (NULL);

	k = 0;
	while (k < len)
	{
		newstr[k] = s1[start + k];
		k++;
	}
	newstr[k] = '\0';
	return (newstr);
}
