/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:20:20 by karamire          #+#    #+#             */
/*   Updated: 2025/07/21 02:53:13 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	no_env_build(t_main *main)
{
	char	buff[1024];
	char	*pwd;
	char	*shlvl;
	t_env	*mainenv;
	t_env	*tmp;

	getcwd(buff, 1024);
	pwd = ft_strjoin("PWD=", buff);
	if (!pwd)
		free_and_exit_error(main, NULL, ERR_MEM, 12);
	mainenv = lstnew(pwd);
	if (!mainenv)
		free_and_exit_error(main, pwd, ERR_MEM, 12);
	main->env = mainenv;
	mainenv->next = NULL;
	shlvl = ft_strdup("SHLVL=1");
	if (!shlvl)
		free_and_exit_error(main, NULL, ERR_MEM, 12);
	tmp = lstnew(shlvl);
	if (!tmp)
		free_and_exit_error(main, shlvl, ERR_MEM, 12);
	lstadd_back(&mainenv, tmp);
}

void	env_build(char **env, t_main *main)
{
	int		i;
	char	*str;
	t_env	*mainenv;

	str = ft_strdup(env[0]);
	if (!str)
		free_and_exit_error(main, NULL, ERR_MEM, 12);
	mainenv = lstnew(str);
	if (!mainenv)
		free_and_exit_error(main, str, ERR_MEM, 12);
	main->env = mainenv;
	i = 1;
	while (env[i] != NULL)
	{
		str = ft_strdup(env[i]);
		if (!str)
			free_and_exit_error(main, NULL, ERR_MEM, 12);
		lstadd_back(&mainenv, lstnew(str));
		i++;
	}
}

int	check_env_available(char **env, t_main *main)
{
	char	*str;

	str = getenv("PATH");
	if (str == NULL)
		no_env_build(main);
	else
		env_build(env, main);
	return (0);
}
