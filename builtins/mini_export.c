/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:24:55 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/02 20:22:18 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	export_new_var(t_main *main, char *var)
{
	int		i;
	char	*new;

	i = 0;
	while (var[i] != '=')
		i++;
	new = ft_strdup(var);
	lstadd_back(&main->mainenv, lstnew(new));
}
void	replace_var(t_main *main, char *var, t_env *env)
{
	char	*new;

	new = ft_strdup(var);
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
	env = main->mainenv;
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

	env = main->mainenv;
	while (env != NULL)
	{
		write(1, "declare -x ", 11);
		ft_putendl_fd(env->env, 1);
		env = env->next;
	}
}

bool	mini_export(t_main *main)
{
	int		i;
	char	**tab;

	tab = main->node->cmd;
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
