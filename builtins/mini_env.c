/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:52:10 by karamire          #+#    #+#             */
/*   Updated: 2025/05/26 17:09:36 by kaissramire      ###   ########.fr       */
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
int	env_print(t_main *main)
{
	t_env	*temp;

	temp = main->mainenv;
	while (temp)
	{
		ft_putstr_fd(temp->env, 1);
		write(1, "\n", 1);
		temp = temp->next;
	}
	return (0);
}

t_env	*env_build(char **env)
{
	int		i;
	char	*str;
	t_env	*mainenv;

	mainenv = malloc(sizeof(t_env));
	if (!mainenv)
		handle_error_exit(ERR_MALLOC, 12);
	mainenv->env = ft_strdup(env[0]);
	i = 1;
	while (env[i] != NULL)
	{
		str = ft_strdup(env[i]);
		lstadd_back(&mainenv, lstnew(str));
		i++;
	}
	return (mainenv);
}
