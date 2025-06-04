/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:57:04 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/04 20:08:01 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	env_pwd_update(t_main *main)
{
	t_env	*temp;
	char	*tmp;
	int		i;
	char	path[1024];

	i = 0;
	if (getcwd(path, 1024) == NULL)
		free_and_exit_error(main, ERR_GETCWD, errno);
	temp = main->mainenv;
	while (ft_strstr(temp->env, "PWD=") != 1)
		temp = temp->next;
	if (temp->env != NULL)
	{
		free(temp->env);
		tmp = ft_strjoin("PWD=", path);
		if (!tmp)
			free_and_exit_error(main, ERR_MALLOC, 12);
		temp->env = tmp;
	}
}

void	env_oldpwd_update(t_main *main)
{
	t_env	*temp;
	int		i;
	char	*path;
	char	pwd[1024];

	i = 0;
	temp = main->mainenv;
	if (getcwd(pwd, 1024) == NULL)
		free_and_exit_error(main, ERR_GETCWD, errno);
	while (temp != NULL && ft_strstr(temp->env, "OLDPWD=") != 1)
		temp = temp->next;
	if (temp != NULL)
	{
		free(temp->env);
		temp->env = ft_strjoin("OLDPWD=", pwd);
		if (!temp->env)
			free_and_exit_error(main, ERR_MALLOC, 12);
	}
	else
	{
		path = ft_strjoin("OLDPWD=", pwd);
		if (!path)
			free_and_exit_error(main, ERR_MALLOC, 12);
		lstadd_back((&main->mainenv), lstnew(path));
	}
}

char	*cd_to_home(t_main *main, char *path)
{
	t_env	*env;
	char	*str;
	char	*dst;

	env = main->mainenv;
	while (env)
	{
		if (ft_strncmp(env->env, "HOME=", 5) == 0)
		{
			str = ft_strdup(env->env + 5);
			if (!str)
				free_and_exit_error(main, ERR_MALLOC, 12);
		}
		env = env->next;
	}
	if (path)
	{
		dst = ft_strjoin(str, path + 1);
		printf("%s\n", dst);
		if (!dst)
			free_and_exit_error(main, ERR_MALLOC, 12);
	}
	else
		dst = str;
	return (dst);
}

bool	mini_cd(char *line, t_main *main)
{
	char	**tab;
	char	*str;

	env_oldpwd_update(main);
	tab = main->node->cmd;
	if (tab[1] == NULL || tab[1][0] == '~')
		str = cd_to_home(main, tab[1]);
	else
		str = ft_strdup(tab[1]);
	if (chdir(str) == -1)
	{
		perror("chdir error");
		free(str);
		return (false);
	}
	free(str);
	env_pwd_update(main);
	return (true);
}
