/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:57:04 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/03 21:53:16 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	free_and_exit_error(t_main *main, char *error, int err_number)
{
	free_struct(main);
	perror(error);
	exit(err_number);
}
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

bool	mini_cd(char *line, t_main *main)
{
	char	**tab;

	env_oldpwd_update(main);
	tab = main->node->cmd;
	if (tab[1])
	{
		if (chdir(tab[1]) == -1)
			free_and_exit_error(main, ERR_CHDIR, errno);
	}
	else
	{
		if (chdir("~") == -1)
			free_and_exit_error(main, ERR_CHDIR, errno);
	}
	env_pwd_update(main);
	return (true);
}
