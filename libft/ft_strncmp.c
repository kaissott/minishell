/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 07:29:25 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 11:42:21 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && (s1[i] || s2[i]) && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* int	main(void)
{
	char *big = "abcdef";
    char *little = "abcdefghijklmnop";
    size_t size = 6;
    int i2 = ((ft_strncmp(big, little, size) > 0) ? 1 :
	((ft_strncmp(big, little, size) < 0) ? -1 : 0));
	printf("%d", i2);
} */
