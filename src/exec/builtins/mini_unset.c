/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:40:41 by karamire          #+#    #+#             */
/*   Updated: 2025/07/23 10:04:02 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env_node(t_env **env, char *var)
{
	t_env	*current;
	t_env	*temp;

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

bool	mini_unset(t_shell *main, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		return (0);
	if (cmd[1][0] == '-')
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd("': invalid option", 2);
		main->errcode = 2;
		return (0);
	}
	while (cmd[i])
	{
		if (main->env && cmd[1])
			delete_env_node(&main->env, cmd[i]);
		i++;
	}
	return (true);
}
