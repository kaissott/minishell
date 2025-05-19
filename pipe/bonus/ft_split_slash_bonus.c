/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_slash_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:21:25 by kkarakus          #+#    #+#             */
/*   Updated: 2025/03/22 22:05:47 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static char	*substr_slash(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;
	size_t	slen;

	slen = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	newstr = ft_calloc(len + 2, sizeof(char));
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		newstr[i] = s[start];
		i++;
		start++;
	}
	newstr[i] = '/';
	return (newstr);
}

static int	ft_countwords(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static char	**ft_free(char **tab, int j)
{
	while (j > 0)
	{
		j--;
		free(tab[j]);
	}
	free(tab);
	return (NULL);
}

static char	**ft_tabcomp(char **tab, char const *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			tab[j] = substr_slash(s, start, (i - start));
			if (tab[j] == NULL)
				return (ft_free(tab, j));
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split_slash(char const *s, char c)
{
	char	**tab;

	if (s == NULL)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	return (ft_tabcomp(tab, s, c));
}

/* int	main(void)
{
	char const	*phrase;
	char		**resultat;

	phrase = "Hello,World,From,Split";
	resultat = ft_split(phrase, 'o');
	printf("%s\n", resultat[0]);
	printf("%s\n", resultat[1]);
	printf("%s\n", resultat[2]);
	printf("%s\n", resultat[3]);
	printf("%s\n", resultat[4]);
}
// --> Compiler avec split, substr, strlen et strdup */
