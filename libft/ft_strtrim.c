/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:34:49 by ludebion          #+#    #+#             */
/*   Updated: 2025/09/01 21:36:29 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	char_is_in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_start_str(const char *s, const char *set)
{
	size_t	i;

	i = 0;
	while (char_is_in_set(s[i], set))
		i++;
	return (i);
}

static size_t	get_end_str(const char *s, const char *set)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	while (char_is_in_set(s[i], set) && i > 0)
		i--;
	return (ft_strlen(s) - i - 1);
}

static char	*fill_str(const char *s1, char *s, size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while ((start + i) < end)
	{
		s[i] = s1[start + i];
		i++;
	}
	return (s);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	size_t	start;
	size_t	end;
	size_t	total_len;

	if (!s1 || !set)
		return (NULL);
	start = get_start_str(s1, set);
	end = get_end_str(s1, set);
	total_len = ft_strlen(s1) - start - end;
	if (ft_strlen(s1) == start)
		total_len = 0;
	s = ft_calloc((total_len + 1), sizeof(char));
	if (!s)
		return (NULL);
	return (fill_str(s1, s, start, ft_strlen(s1) - end));
}
