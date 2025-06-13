/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:44:21 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/24 03:57:20 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cs;

	cs = (unsigned char *)s;
	i = 0;
	c = (unsigned char)c;
	while (i < n)
	{
		if (cs[i] == c)
			return (&cs[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char	s[] = "Hello world";
// 	const char	s2[] = "";
// 	const char	s3[] = "\0";
// 	const char	*s4;
// 	char		*ret;
// 	char		*retv;
// 	char		*ret2;
// 	char		*ret2v;
// 	char		*ret3;
// 	char		*ret3v;
// 	char		*ret4;
// 	char		*ret4v;
// 	char		*ret5;
// 	char		*ret5v;
// 	char		*ret6;
// 	char		*ret6v;
// 	char		*ret7;
// 	char		*ret7v;
// 	int			c;
// 	size_t		n;
// 	int			c2;
// 	int			c3;
// 	int			c4;

// 	n = 9;
// 	c = 119;
// 	c2 = '9';
// 	c3 = 32;
// 	c4 = '\0';
// 	ret = ft_memchr(s, c, n);
// 	retv = memchr(s, c, n);
// 	ret2 = ft_memchr(s, c2, n);
// 	ret2v = memchr(s, c2, n);
// 	ret3 = ft_memchr(s, c3, n);
// 	ret3v = memchr(s, c3, n);
// 	ret4 = ft_memchr(s, c4, n);
// 	ret4v = memchr(s, c4, n);
// 	ret5 = ft_memchr(s2, c4, n);
// 	ret5v = memchr(s2, c4, n);
// 	ret6 = ft_memchr(s3, c3, n);
// 	ret6v = memchr(s3, c3, n);
// 	ret7 = ft_memchr(s4, c3, n);
// 	ret7v = memchr(s4, c3, n);
// 	printf("c = w : %s\n", ret);
// 	printf("c = w (vraie) : %s\n\n", ret);
// 	printf("c = 9 : %s\n", ret2);
// 	printf("c = 9 (vraie) : %s\n\n", ret2v);
// 	printf("c = esp : %s\n", ret3);
// 	printf("c = esp (vraie) : %s\n\n", ret3v);
// 	printf("c = \\0 : %s\n", ret4);
// 	printf("c = \\0 (vraie) : %s\n\n", ret4v);
// 	printf("c = \\0 s2 = vide : %s\n", ret5);
// 	printf("c = \\0 s2 = vide (vraie) : %s\n\n", ret5v);
// 	printf("c = esp s3 = \\0 : %s\n", ret6);
// 	printf("c = esp s3 = \\0 (vraie) : %s\n\n", ret6v);
// 	printf("c = esp s3 = vide : %s\n", ret7);
// 	printf("c = esp s3 = vide (vraie) : %s\n\n", ret7v);
// 	return (0);
// }
