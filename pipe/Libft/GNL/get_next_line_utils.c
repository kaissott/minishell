/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:34:12 by kaissramire       #+#    #+#             */
/*   Updated: 2025/03/24 17:50:46 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_slen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = malloc((ft_slen(s1) + ft_slen(s2) + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (free(s1), str);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	c = (char)c;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return ((char *)s + i);
	return (NULL);
}

void	*ftmemcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = dest;
	s = src;
	i = 0;
	if ((dest == 0 && src == 0) || n == 0)
		return ((unsigned char *)dest);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return ((unsigned char *)dest);
}
