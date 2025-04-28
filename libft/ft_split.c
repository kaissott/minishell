/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 03:31:13 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/24 07:43:09 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_arr(char **strs, size_t count)
{
	while (count > 0)
	{
		count--;
		free(strs[count]);
	}
	free(strs);
	return (NULL);
}

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static size_t	calc_strs_len(const char *str, char c, size_t start)
{
	size_t	i;

	i = 0;
	while (str[start + i])
	{
		if (str[start + i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	strs = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (calc_strs_len(s, c, i) != 0)
		{
			strs[j] = ft_substr(s, i, calc_strs_len(s, c, i));
			if (!strs[j])
				return (free_arr(strs, j));
			i += calc_strs_len(s, c, i);
			j++;
		}
		else
			i++;
	}
	return (strs);
}
// int	main(void)
// {
// 	char	c;
// 	int		size;
// 	int		i;
// 	char	**strs;
// 	char	str[] = "  . Aller. .l'OL  ";

// 	c = ' ';
// 	size = 0;
// 	i = 0;
// 	strs = ft_split(NULL, c);
// 	while (strs[size])
// 		size++;
// 	printf("Size strs : [%d]\n", size);
// 	while (strs[i])
// 	{
// 		printf("Ma str [%d] dans strs : \"%s\"\n", i, strs[i]);
// 		i++;
// 	}
// 	return (0);
// }
