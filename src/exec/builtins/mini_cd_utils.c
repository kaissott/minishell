/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:35:44 by karamire          #+#    #+#             */
/*   Updated: 2025/07/24 21:24:34 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_pwd_update(t_shell *main)
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
		pwd();
}

void	env_oldpwd_update(t_shell *main)
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
		lstadd_back_env((&main->env), lstnew_env(path, main));
	}
}
