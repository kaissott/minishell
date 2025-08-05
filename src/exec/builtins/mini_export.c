/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:24:55 by karamire          #+#    #+#             */
/*   Updated: 2025/07/30 21:36:20 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var_exist(t_shell *main, char *var)
{
	int		i;
	t_env	*env;

	i = 0;
	while (var[i] != '=')
		i++;
	env = main->env;
	while (env != NULL)
	{
		if (ft_strncmp(var, env->env, i) == 0)
		{
			replace_var(main, var, env);
			return (0);
		}
		env = env->next;
	}
	return (-1);
}

bool	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	print_export_env(t_shell *main)
{
	t_env	*env;

	env = main->env;
	while (env != NULL)
	{
		if (ft_putendl_fd(env->env, 1) == -1)
			free_and_exit_error(main, NULL, ERR_WRITE, errno);
		env = env->next;
	}
}

bool	mini_export(t_shell *main, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		print_export_env(main);
	while (cmd[i])
	{
		if (!is_valid_identifier(cmd[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			if (cmd[i][0] == '-')
				main->errcode = 2;
			else
				main->errcode = 1;
		}
		else if (ft_strchr(cmd[i], '=') != NULL)
		{
			if (check_var_exist(main, cmd[i]) == -1)
				export_new_var(main, cmd[i]);
		}
		i++;
	}
	return (true);
}
