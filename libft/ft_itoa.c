/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:54:13 by karamire          #+#    #+#             */
/*   Updated: 2024/11/20 13:27:47 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numsize(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n <= 0)
	{
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;

	size = ft_numsize(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = malloc(sizeof (char) * (size + 1));
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	str[size] = '\0';
	while (n != 0)
	{
		str[size - 1] = (n % 10) + '0';
		n = n / 10;
		size--;
	}
	return (str);
}

/* int	main(void)
{
	int	a = -2147483648;

	printf("a = %s\n", ft_itoa(a));
} */
/*  int	main(void)
{
	unsigned int	a = 2147483648;

	printf("a = %s\n", ft_itoa(a));
} */
