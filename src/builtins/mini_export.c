/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:24:55 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/13 16:48:39 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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
		free_and_exit_error(main, ERR_MALLOC, 12);
	export = lstnew(new);
	if (!export)
		free_and_exit_error(main, ERR_MALLOC, 12);
	lstadd_back(&main->env, export);
}
void	replace_var(t_main *main, char *var, t_env *env)
{
	char	*new;

	new = ft_strdup(var);
	if (!new)
		free_and_exit_error(main, ERR_MALLOC, 12);
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

void	print_export_env(t_main *main)
{
	t_env	*env;

	env = main->env;
	while (env != NULL)
	{
		if (write(1, "declare -x ", 11) == -1)
			free_and_exit_error(main, ERR_WRITE, errno);
		if (ft_putendl_fd(env->env, 1) == -1)
			free_and_exit_error(main, ERR_WRITE, errno);
		env = env->next;
	}
}

bool	mini_export(t_main *main)
{
	int		i;
	char	**tab;

	tab = main->exec->cmd;
	;
	i = 1;
	if (tab[1] == NULL)
		print_export_env(main);
	while (tab[i])
	{
		if (ft_strchr(tab[i], '=') != NULL)
		{
			if (check_var_exist(main, tab[i]) == -1)
				export_new_var(main, tab[i]);
		}
		i++;
	}
	return (true);
}
