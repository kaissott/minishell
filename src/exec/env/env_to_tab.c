/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:40:09 by karamire          #+#    #+#             */
/*   Updated: 2025/07/24 08:19:01 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_tab(t_shell *main)
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
	if (tab == NULL)
		free_and_exit_error(main, NULL, ERR_MEM, 12);
	tmp = main->env;
	j = 0;
	while (i-- > 0)
	{
		tab[j++] = tmp->env;
		tmp = tmp->next;
	}
	tab[j] = NULL;
	return (tab);
}
