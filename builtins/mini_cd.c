/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:57:04 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/10 20:55:47 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	mini_cd(char *line)
{
	char	**tab;

	tab = ft_split(line, ' ');
	if (tab[1])
	{
		if (chdir(tab[1]) == -1)
			printf("nul");
	}
}
