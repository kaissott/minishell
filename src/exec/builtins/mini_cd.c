/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:57:04 by kaissramire       #+#    #+#             */
/*   Updated: 2025/07/17 23:43:14 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	env_pwd_update(t_main *main)
{
	t_env	*temp;
	char	*tmp;
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		free_and_exit_error(main, NULL, ERR_GETCWD, errno);
	temp = main->env;
	while (temp != NULL && ft_strnstr(temp->env, "PWD=", 4) == NULL)
		temp = temp->next;
	if (temp != NULL)
	{
		free(temp->env);
		tmp = ft_strjoin("PWD=", path);
		if (!tmp)
			free_and_exit_error(main, NULL, ERR_MEM, 12);
		temp->env = tmp;
	}
	else
		pwd(main);
}

void	env_oldpwd_update(t_main *main)
{
	t_env	*temp;
	char	*path;
	char	pwd[1024];

	temp = main->env;
	if (getcwd(pwd, 1024) == NULL)
		free_and_exit_error(main, NULL, ERR_GETCWD, errno);
	while (temp != NULL && ft_strstr(temp->env, "OLDPWD=") != 1)
		temp = temp->next;
	if (temp != NULL)
	{
		free(temp->env);
		temp->env = ft_strjoin("OLDPWD=", pwd);
		if (!temp->env)
			free_and_exit_error(main, NULL, ERR_MEM, 12);
	}
	else
	{
		path = ft_strjoin("OLDPWD=", pwd);
		if (!path)
			free_and_exit_error(main, NULL, ERR_MEM, 12);
		lstadd_back((&main->env), lstnew(path));
	}
}

char	*cd_to_home(t_main *main, char *path, int i)
{
	t_env	*env;
	char	*str;
	char	*dst;

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
	if (path)
	{
		dst = ft_strjoin(str, path + i);
		if (!dst)
			free_and_exit_error(main, NULL, ERR_MEM, 12);
		free(str);
	}
	else
		dst = str;
	return (dst);
}

char	*cd_to_last_pwd(t_main *main)
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
			if (!str)
				free_and_exit_error(main, NULL, ERR_MEM, 12);
			printf("%s\n", str);
			return (str);
		}
		env = env->next;
	}
	ft_putendl_fd("bash: cd: OLDPWD not set", 2);
	main->errcode = 1;
	return (str);
}

char	*get_directory(t_main *main, char **tab)
{
	char	*str;

	str = NULL;
	if (tab[1] == NULL || tab[1][0] == '~')
		str = cd_to_home(main, tab[1], 1);
	else if ((ft_strcmp(tab[1], "--") == 0))
		str = cd_to_home(main, tab[1], 2);
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

bool	mini_cd(char **cmd, t_main *main)
{
	char	*str;

	if (cmd[1] != NULL && cmd[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		main->errcode = 1;
		return (true);
	}
	str = get_directory(main, cmd);
	if (access(str, F_OK) == 0 && access(str, X_OK) == 0)
	{
		env_oldpwd_update(main);
		if (chdir(str) != -1)
		{
			env_pwd_update(main);
			free(str);
		}
	}
	else
	{
		free(str);
		ft_putstr_fd("bash: cd: ", 2);
		return (set_return_err_code(main, main->exec->cmd[1], 1));
	}
	return (true);
}
