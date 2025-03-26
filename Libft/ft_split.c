/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:21:25 by kkarakus          #+#    #+#             */
/*   Updated: 2025/03/20 16:08:16 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
			tab[j] = ft_substr(s, start, (i - start));
			if (tab[j] == NULL)
				return (ft_free(tab, j));
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		count;

	count = ft_countwords(s, c);
	if (s == NULL || count == 0)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
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
