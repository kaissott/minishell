/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:40:09 by karamire          #+#    #+#             */
/*   Updated: 2025/06/14 05:22:52 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_to_tab(t_main *main)
{
	int		i;
	int		j;
	char	**tab;
	t_env	*tmp;

	i = 0;
	tmp = main->env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		free_and_exit_error(main, ERR_MEM, 12);
	tmp = main->env;
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
