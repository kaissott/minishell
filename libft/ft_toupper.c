/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:33:14 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/24 10:26:26 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ((c >= 'a' && c <= 'z'))
		return (c - 32);
	return (c);
}

// int	main(void)
// {
// 	printf("La lettre avant : %c\n", 'a');
// 	printf("La lettre apres : %c\n", ft_toupper('a'));
// 	printf("La lettre apres (vraie) : %c\n\n", toupper('a'));
// 	//
// 	printf("La lettre avant : %c\n", 'A');
// 	printf("La lettre apres : %c\n", ft_toupper('A'));
// 	printf("La lettre apres (vraie) : %c\n\n", toupper('a'));
// 	//
// 	printf("La lettre avant : %c\n", '6');
// 	printf("La lettre apres : %c\n", ft_toupper('6'));
// 	printf("La lettre apres (vraie) : %c\n\n", toupper('6'));
// 	//
// 	printf("La lettre avant : %c\n", ' ');
// 	printf("La lettre apres : %c\n", ft_toupper(' '));
// 	printf("La lettre apres (vraie) : %c\n", toupper(' '));
// }
