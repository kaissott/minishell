/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:49:29 by karamire          #+#    #+#             */
/*   Updated: 2025/07/02 18:58:33 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_tabs(char **tab1, char **tab2)
{
	int	i;

	i = 0;
	if (tab1)
	{
		while (tab1[i])
		{
			free(tab1[i]);
			i++;
		}
		free(tab1);
	}
	i = 0;
	if (tab2)
	{
		while (tab2[i])
			free(tab2[i++]);
		free(tab2);
	}
}
