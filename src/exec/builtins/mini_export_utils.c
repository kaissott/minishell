/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:38:41 by karamire          #+#    #+#             */
/*   Updated: 2025/07/24 08:18:46 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_new_var(t_shell *main, char *var)
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
	export = lstnew_env(new, main);
	lstadd_back_env(&main->env, export);
}

void	replace_var(t_shell *main, char *var, t_env *env)
{
	char	*new;

	new = ft_strdup(var);
	if (!new)
		free_and_exit_error(main, NULL, ERR_MEM, 12);
	free(env->env);
	env->env = new;
}
