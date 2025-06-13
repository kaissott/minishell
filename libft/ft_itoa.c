/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:43:54 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/18 09:23:29 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_nb_len(int n)
{
	int	res;

	res = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		res++;
		n *= -1;
	}
	while (n > 0)
	{
		res++;
		n /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	int		nb_len;
	char	*res;
	int		n2;

	n2 = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nb_len = calc_nb_len(n);
	res = ft_calloc((nb_len + 1), sizeof(char));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		n2 = n * -1;
	}
	while (--nb_len >= 0 && (res[nb_len] != '-'))
	{
		res[nb_len] = n2 % 10 + '0';
		n2 /= 10;
	}
	return (res);
}

// int	main(void)
// {
// 	int	n;
// 	int	n1;
// 	int	n2;
// 	int	n3;
// 	int	n4;
// 	int	n5;
// 	int	n6;
// 	int	n7;

// 	n = 0;
// 	n1 = -1;
// 	n2 = 9;
// 	n3 = 69;
// 	n4 = -2147483648;
// 	n5 = -2147483647;
// 	n6 = 2147483647;
// 	n7 = -70;
// 	printf("n = 0 : %s\n", ft_itoa(n));
// 	printf("n1 = -1 : %s\n", ft_itoa(n1));
// 	printf("n2 = 9 : %s\n", ft_itoa(n2));
// 	printf("n3 = 69 : %s\n", ft_itoa(n3));
// 	printf("n4 = -2147483648 : %s\n", ft_itoa(n4));
// 	printf("n5 = -2147483647 : %s\n", ft_itoa(n5));
// 	printf("n6 = 2147483647 : %s\n", ft_itoa(n6));
// 	printf("n7 = -70 : %s\n", ft_itoa(n7));
// 	return (0);
// }
