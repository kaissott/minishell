/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:33:35 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 14:08:10 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_starttrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (set[j])
	{
		if (set[j] == s1[i])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static int	ft_endtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j] && i > 0)
	{
		if (set[j] == s1[i])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*newstr;

	if ((s1 == NULL && set == NULL))
		return (NULL);
	i = ft_starttrim(s1, set);
	j = ft_endtrim(s1, set) + 1;
	if (i == ft_strlen(s1))
		newstr = malloc(1);
	else
		newstr = malloc((j - i) + 1);
	if (newstr == NULL)
		return (NULL);
	k = 0;
	while (i < j)
	{
		newstr[k] = s1[i];
		k++;
		i++;
	}
	newstr[k] = '\0';
	return (newstr);
}
