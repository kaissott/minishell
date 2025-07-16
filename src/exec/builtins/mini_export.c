
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:24:55 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/16 00:16:31 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	export_new_var(t_main *main, char *var)
{
	int		i;
	char	*new;
	t_env	*export;

	i = 0;
	while (var[i] != '=')
		i++;
	new = ft_strdup(var);
	if (!new)
		free_and_exit_error(main, NULL, ERR_MEM, 12);
	export = lstnew(new);
	if (!export)
		free_and_exit_error(main, NULL, ERR_MEM, 12);
	lstadd_back(&main->env, export);
}
void	replace_var(t_main *main, char *var, t_env *env)
{
	char	*new;

	new = ft_strdup(var);
	if (!new)
		free_and_exit_error(main, NULL, ERR_MEM, 12);
	free(env->env);
	env->env = new;
}
int	check_var_exist(t_main *main, char *var)
{
	int		i;
	char	*new;
	char	*temp;
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

void	print_export_env(t_main *main)
{
	t_env	*env;

	env = main->env;
	while (env != NULL)
	{
		if (write(1, "declare -x ", 11) == -1)
			free_and_exit_error(main, NULL, ERR_WRITE, errno);
		if (ft_putendl_fd(env->env, 1) == -1)
			free_and_exit_error(main, NULL, ERR_WRITE, errno);
		env = env->next;
	}
}

bool	mini_export(t_main *main, char **cmd)
{
	int		i;

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
