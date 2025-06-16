/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:40:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/16 03:06:56 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*try_paths(t_main *main, char **paths, char **env, char *env_path)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], main->exec->cmd[0]);
		if (!full_path)
		{
			free_tab_2(paths);
			free(env);
			free_and_exit_error(main, env_path, ERR_MEM, 12);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_tab_2(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tab_2(paths);
	return (NULL);
}

char	*get_path(t_main *main, char *env_path, char **env)
{
	char	**paths;
	char	*result;

	paths = ft_split_slash(env_path, ':');
	if (!paths)
	{
		free(env);
		free_and_exit_error(main, env_path, ERR_MEM, 12);
	}
	result = try_paths(main, paths, env_path, env);
	return (result);
}

char	*env_path_finding(t_main *main, char **env)
{
	char	*env_path;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			env_path = ft_strdup(env[i]);
			if (env_path == NULL)
				free_and_exit_error(main, env, ERR_MEM, 12);
			return (env_path);
		}
		i++;
	}
	return (NULL);
}
void	exec_simple_cmd(t_main *main)
{
	char	*env_path;
	char	*path;
	char	**env;

	env = env_to_tab(main);
	if (strrchr_slash(main->exec->cmd[0], '/'))
	{
		execve(main->exec->cmd[0], main->exec->cmd, env);
	}
	env_path = env_path_finding(main, env);
	path = get_path(main, env_path, env);
	if (path == NULL)
	{
		free(env_path);
		free(path);
		free(env);
		free_and_exit_error(main, env_path, "Command not found", 12);
		return;
	}
	execve(path, main->exec->cmd, env);
}


void	init_simple_cmd(t_main *main)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fork_error(main, ERR_FORK);
	if (pid == 0)
		exec_simple_cmd(main);
	wait(NULL);
}
