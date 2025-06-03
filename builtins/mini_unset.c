/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:41:17 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/03 22:06:01 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdlib.h>
#include <string.h>

void	delete_env_node(t_env **env, char *var)
{
	t_env	*current;
	t_env	*temp;

	if (!env || !var)
		return ;
	current = *env;
	if (ft_strncmp(current->env, var, ft_strlen(var)) == 0
		&& (current->env[ft_strlen(var)]) == '=')
	{
		*env = current->next;
		free(current->env);
		free(current);
		return ;
	}
	while (current->next)
	{
		if (ft_strncmp(current->next->env, var, ft_strlen(var)) == 0
			&& (current->next->env[ft_strlen(var)]) == '=')
		{
			temp = current->next;
			current->next = temp->next;
			free(temp->env);
			free(temp);
			return ;
		}
		current = current->next;
	}
}

bool	mini_unset(t_main *main)
{
	char	**cmd;
	int		i;

	i = 1;
	cmd = main->node->cmd;
	if (cmd[1] == NULL)
		return (0);
	while (cmd[i])
	{
		delete_env_node(&main->mainenv, cmd[i]);
		i++;
	}
	return (true);
}
