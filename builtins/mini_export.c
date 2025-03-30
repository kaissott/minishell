/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:21:38 by karamire          #+#    #+#             */
/*   Updated: 2025/03/30 22:05:36 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	export_print_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		write(1, "declare -x ", 11);
		write(1, temp->env, ft_strlen(temp->env));
		write(1, "\n", 1);
		temp = temp->next;
	}
	return (0);
}

int	check_new_var(t_cmd *cmd)
{
	t_cmd	temp;
	int		i;
	int		j;

	i = 0;
	while (cmd->args[i] != NULL)
	{
		j = 0;
		while (cmd->args[i][j])
		{
			if(cmd->args[i])
		}
	}
}
int	export_parsing(t_cmd *cmd, t_env *env)
{
	if (cmd->args == NULL)
		export_print_env(env);
	else if (check_new_var(cmd) == 1)
		add_new_var(cmd, env);
	return (0);
}
