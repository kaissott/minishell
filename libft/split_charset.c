/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_charset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:33:36 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/28 01:02:35 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_strs(char **strs)
{
	size_t	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

static char	**resize_strs(char **strs, char *new_arg)
{
	size_t	len;
	char	**new_strs;

	len = 0;
	while (strs && strs[len])
		len++;
	new_strs = ft_calloc(len + 2, sizeof(char *));
	if (!new_strs)
	{
		free_strs(strs);
		return (NULL);
	}
	if (strs)
		ft_memcpy(new_strs, strs, len * sizeof(char *));
	new_strs[len] = new_arg;
	return (new_strs);
}

static bool	is_in_charset(char *charset, char c)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (true);
		i++;
	}
	return (false);
}

static ssize_t	extract_word(char ***strs_ptr, char *s, char *charset)
{
	size_t	i;
	char	*word;
	char	**new_strs;

	i = 0;
	if (!s[i])
		return (0);
	while (s[i] && !is_in_charset(charset, s[i]))
		i++;
	word = ft_substr(s, 0, i);
	if (!word)
		return (-1);
	new_strs = resize_strs(*strs_ptr, word);
	if (!new_strs)
	{
		free(word);
		return (-1);
	}
	free(*strs_ptr);
	*strs_ptr = new_strs;
	return (i);
}

char	**split_charset(char *s, char *charset)
{
	ssize_t	i;
	char	**strs;
	ssize_t	ret;

	i = 0;
	strs = NULL;
	while (s[i])
	{
		while (s[i] && is_in_charset(charset, s[i]))
			i++;
		ret = extract_word(&strs, &s[i], charset);
		if (ret == -1)
			return (NULL);
		i += ret;
	}
	return (strs);
}

// int	main(int ac, char **av)
// {
// 	size_t	i;
// 	char	**split;

// 	(void)ac;
// 	i = 0;
// 	split = split_charset(av[1], av[2]);
// 	if (!split)
// 	{
// 		printf("\tError in split\n");
// 		return (EXIT_FAILURE);
// 	}
// 	while (split[i])
// 	{
// 		printf("Split n°%zu :\n\t [%s]\n", i, split[i]);
// 		i++;
// 	}
// 	free_strs(split);
// 	return (EXIT_SUCCESS);
// }
