/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:33:14 by ludebion          #+#    #+#             */
/*   Updated: 2024/11/16 17:34:54 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ((c >= 'A' && c <= 'Z'))
		return (c + 32);
	return (c);
}

// int	main(void)
// {
// 	printf("La lettre avant : %c\n", 'a');
// 	printf("La lettre apres : %c\n", ft_tolower('a'));
// 	printf("La lettre apres (vraie) : %c\n\n", tolower('a'));
// 	//
// 	printf("La lettre avant : %c\n", 'A');
// 	printf("La lettre apres : %c\n", ft_tolower('A'));
// 	printf("La lettre apres (vraie) : %c\n\n", tolower('a'));
// 	//
// 	printf("La lettre avant : %c\n", '6');
// 	printf("La lettre apres : %c\n", ft_tolower('6'));
// 	printf("La lettre apres (vraie) : %c\n\n", tolower('6'));
// 	//
// 	printf("La lettre avant : %c\n", ' ');
// 	printf("La lettre apres : %c\n", ft_tolower(' '));
// 	printf("La lettre apres (vraie) : %c\n", tolower(' '));
// }
