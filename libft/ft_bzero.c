/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:18:28 by karamire          #+#    #+#             */
/*   Updated: 2024/11/13 22:17:31 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

/* int	main(void)
{
	int	str[] = {1, 1, 1, 1, 1};
	int	i;

	i = 0;
	while (i < 5)
	{
		printf("%d", str[i]);
		i++;
	}
	bzero(str, sizeof(int) * 4);
	i = 0;
	printf("\n");
	while (i < 5)
	{
		printf("%d", str[i]);
		i++;
	}
}*/
