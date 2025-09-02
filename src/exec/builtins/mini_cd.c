/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:57:04 by karamire          #+#    #+#             */
/*   Updated: 2025/09/02 16:58:13 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	cd_err(t_shell *main, char *err)
{
	ft_putstr_fd(err, 2);
	main->errcode = 1;
	return (true);
}

char	*cd_to_home(t_shell *main)
{
	t_env	*env;
	char	*str;

	str = NULL;
	env = main->env;
	while (env)
	{
		if (ft_strncmp(env->env, "HOME=", 5) == 0)
		{
			str = ft_strdup(env->env + 5);
			if (!str)
				free_and_exit_error(main, NULL, ERR_MEM, 12);
		}
		env = env->next;
	}
	if (!str)
	{
		cd_err(main, "minishell: cd: HOME not set\n");
		return (NULL);
	}
	return (str);
}

char	*cd_to_last_pwd(t_shell *main)
{
	t_env	*env;
	char	*str;

	env = main->env;
	str = NULL;
	while (env)
	{
		if (ft_strncmp(env->env, "OLDPWD=", 7) == 0)
		{
			str = ft_strdup(env->env + 7);
			printf("%s\n", str);
			if (!str)
				free_and_exit_error(main, NULL, ERR_MEM, 12);
			return (str);
		}
		env = env->next;
	}
	cd_err(main, "minishell: cd: OLDPWD not set\n");
	return (str);
}

char	*get_directory(t_shell *main, char **tab)
{
	char	*str;

	str = NULL;
	if (tab[1] == NULL || tab[1][0] == '~')
		str = cd_to_home(main);
	else if ((ft_strcmp(tab[1], "--") == 0))
		str = cd_to_home(main);
	else if (tab[1][0] == '-' && tab[1][1] == '\0')
		str = cd_to_last_pwd(main);
	else
	{
		str = ft_strdup(tab[1]);
		if (str == NULL)
			free_and_exit_error(main, str, ERR_MEM, 12);
	}
	return (str);
}

bool	mini_cd(char **cmd, t_shell *main)
{
	char	*str;

	if (cmd[1] != NULL && cmd[2])
		return (cd_err(main, "minishell: cd: HOME not set\n"));
	str = get_directory(main, cmd);
	if (!str)
		return (false);
	if (access(str, F_OK) == 0 && access(str, X_OK) == 0)
	{
		env_oldpwd_update(main);
		if (chdir(str) != -1)
		{
			free(str);
			env_pwd_update(main);
		}
	}
	else
	{
		free(str);
		cd_err(main, "minishell: cd: ");
		return (set_return_err_code(main, main->exec->cmd[1], 1));
	}
	return (true);
}
