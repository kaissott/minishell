/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_global_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 00:27:16 by karamire          #+#    #+#             */
/*   Updated: 2025/07/23 18:06:38 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_current_dir_exec(t_shell *main, char **cmd)
{
	char	*filepath;

	if (!main || !main->exec || !main->exec->cmd || !main->exec->cmd[0])
		return (0);
	filepath = ft_strjoin("./", cmd[0]);
	if (!filepath)
		return (0);
	if (access(filepath, F_OK) != 0)
	{
		free(filepath);
		free_and_exit_error(main, NULL, "No such file or directory", 127);
	}
	if (access(filepath, X_OK) != 0)
	{
		free(filepath);
		free_and_exit_error(main, NULL, "Permission denied", 126);
	}
	execve(filepath, main->exec->cmd, main->env_tab);
	free(filepath);
	return (1);
}

static char	*try_paths(t_shell *main, char **paths, char *env_path)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], main->exec->cmd[0]);
		if (!full_path)
		{
			free_tab(paths);
			free_and_exit_error(main, env_path, ERR_MEM, 12);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_tab(paths);
			free(env_path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

char	*get_path(t_shell *main, char *env_path, char **env)
{
	char	**paths;
	char	*result;

	if (!env_path)
		return (NULL);
	paths = ft_split_slash(env_path, ':');
	if (!paths)
		free_and_exit_error(main, env_path, ERR_MEM, 12);
	result = try_paths(main, paths, env_path);
	return (result);
}

char	*env_path_finding(t_shell *main, char **env)
{
	char	*env_path;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			env_path = ft_strdup(ft_strnstr(env[i], "PATH=", 5));
			if (!env_path)
				free_and_exit_error(main, NULL, ERR_MEM, 12);
			return (env_path);
		}
		i++;
	}
	return (NULL);
}

void	ultimate_path_check(t_shell *main, char **cmd)
{
	if (strrchr_slash(cmd[0], '/') == 1)
	{
		if (opendir(cmd[0]))
		{
			closedir(opendir(cmd[0]));
			free_and_exit_error(main, NULL, "Is a directory", 126);
		}
		if (access(cmd[0], F_OK) != 0)
			free_and_exit_error(main, NULL, "No such file or directory", 127);
		if (access(cmd[0], X_OK) != 0)
			free_and_exit_error(main, NULL, "Permission denied", 126);
		execve(cmd[0], cmd, main->env_tab);
		execve_err(main, main->env_tab, NULL, cmd[0]);
	}
}
