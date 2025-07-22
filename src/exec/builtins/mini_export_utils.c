/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:38:41 by karamire          #+#    #+#             */
/*   Updated: 2025/07/22 10:48:17 by karamire         ###   ########.fr       */
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
	export = lstnew_env(new, main);
	if (!export)
		free_and_exit_error(main, NULL, ERR_MEM, 12);
	lstadd_back_env(&main->env, export);
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
