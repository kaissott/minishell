/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:20:20 by karamire          #+#    #+#             */
/*   Updated: 2025/06/02 17:53:25 by karamire         ###   ########.fr       */
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

void	no_env_build(t_main *main)
{
	char	buff[1024];
	char	*pwd;
	char	*shlvl;
	t_env	*mainenv;

	mainenv = malloc(sizeof(t_env));
	if (!mainenv)
		handle_error_exit(ERR_MALLOC, 12);
	getcwd(buff, 1024);
	pwd = ft_strjoin("PWD=", buff);
	mainenv = lstnew(pwd);
	mainenv->next = NULL;
	shlvl = ft_strdup("SHLVL=1");
	lstadd_back(&mainenv, lstnew(shlvl));
	main->mainenv = mainenv;
}

void	env_build(char **env, t_main *main)
{
	int		i;
	char	*str;
	t_env	*mainenv;

	str = ft_strdup(env[0]);
	mainenv = lstnew(str);
	if (!mainenv)
		handle_error_exit(ERR_MALLOC, 12);
	i = 1;
	while (env[i] != NULL)
	{
		str = ft_strdup(env[i]);
		lstadd_back(&mainenv, lstnew(str));
		i++;
	}
	main->mainenv = mainenv;
}

int	check_env_available(char **env, t_main *main)
{
	char	*str;
	t_env	*temp;

	str = getenv("PATH");
	if (str == NULL)
		no_env_build(main);
	else
		env_build(env, main);
	return (0);
}
