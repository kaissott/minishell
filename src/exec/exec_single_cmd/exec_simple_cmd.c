/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:40:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/07/03 20:14:39 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	check_current_dir_exec(t_main *main)
{
	char	*filepath;

	if (!main || !main->exec || !main->exec->cmd || !main->exec->cmd[0])
		return (0);
	filepath = ft_strjoin("./", main->exec->cmd[0]);
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

static char	*try_paths(t_main *main, char **paths, char *env_path, char **env)
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
			free_and_exit_error(main, env_path, ERR_MEM, 12);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_tab_2(paths);
			free(env_path);
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

	if (!env_path)
		return (NULL);
	paths = ft_split_slash(env_path, ':');
	if (!paths)
		free_and_exit_error(main, env_path, ERR_MEM, 12);
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

void	ultimate_path_check(t_main *main, char **cmd)
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
void	exec_simple_cmd(t_main *main)
{
	char	*env_path;
	char	*path;

	main->env_tab = env_to_tab(main);
	ultimate_path_check(main, main->exec->cmd);
	env_path = env_path_finding(main, main->env_tab);
	path = get_path(main, env_path, main->env_tab);
	if (!path)
	{
		if (!env_path && check_current_dir_exec(main))
			return ;
		free(path);
		free(env_path);
		execve_err(main, main->env_tab, path, main->exec->cmd[0]);
		return ;
	}
	execve(path, main->exec->cmd, main->env_tab);
	execve_err(main, main->env_tab, path, main->exec->cmd[0]);
}

void	init_simple_cmd(t_main *main)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		error_fork(NULL, -1, main->exec, main);
	if (pid == 0)
	{
		exit_error_two_close(main, main->std_in, main->std_out);
		exit_error_two_close(main, main->exec->infile.fd,
			main->exec->outfile.fd);
		exec_simple_cmd(main);
	}
	while (waitpid(pid, &status, 0) > 0)
    ;
	if (WIFEXITED(status))
    	main->errcode = WEXITSTATUS(status);
	else
    	main->errcode = 1;
	return ;
}
