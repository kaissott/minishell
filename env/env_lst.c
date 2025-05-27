/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:20:20 by karamire          #+#    #+#             */
/*   Updated: 2025/05/27 19:01:27 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	free_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		env = env->next;
		free(temp->env);
		free(temp);
		temp = env;
	}
}

t_env	*env_build(char **env)
{
	int		i;
	char	*str;
	t_env	*mainenv;

	mainenv = malloc(sizeof(t_env));
	if (!mainenv)
		handle_error_exit(ERR_MALLOC, 12);
	mainenv = lstnew(env[0]);
	i = 1;
	while (env[i] != NULL)
	{
		str = ft_strdup(env[i]);
		lstadd_back(&mainenv, lstnew(str));
		i++;
	}
	return (mainenv);
}
