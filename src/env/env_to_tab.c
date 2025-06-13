/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:40:09 by karamire          #+#    #+#             */
/*   Updated: 2025/06/10 20:31:56 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

char	**env_to_tab(t_main *main)
{
	int		i;
	int		j;
	char	**tab;
	t_env	*tmp;

	i = 0;
	tmp = main->mainenv;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		free_and_exit_error(main, ERR_MALLOC, 12);
	tmp = main->mainenv;
	j = 0;
	while (i > 0)
	{
		tab[j] = tmp->env;
		tmp = tmp->next;
		i--;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
