/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:52:10 by karamire          #+#    #+#             */
/*   Updated: 2025/05/08 21:33:01 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	env_print(t_env *env)
{
	t_env	*temp;

	temp = env;
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
