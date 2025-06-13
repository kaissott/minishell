/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:15:47 by karamire          #+#    #+#             */
/*   Updated: 2025/02/27 23:24:25 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
	return (newstr);
}

/* int	main(void)
{
	char	str[] = "123456789";

	printf("%s\n", ft_substr(str, 1, 20));
} */
