/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:40:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/07/01 23:22:29 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
			free(env);
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

	// if (env_path == NULL)
	// {
	// 	free(env);
	// 	free_and_exit_error(main, env_path, "command not found", 127);
	// }
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
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			env_path = ft_strdup(ft_strnstr(env[i], "PATH=", 5));
			if (!env_path)
				free_and_exit_error(main, env, ERR_MEM, 12);
			return (env_path);
		}
		i++;
	}
	return (NULL);
}

void	execve_error(t_main *main, char **env, char *path)
{
	free(env);
	free_and_exit_error(main, path, "Command not found", 127);
}
void	exec_simple_cmd(t_main *main)
{
	char	*env_path;
	char	*path;

	main->envtab = env_to_tab(main);
	if (strrchr_slash(main->exec->cmd[0], '/') == 1)
	{
		if (opendir(main->exec->cmd[0]))
		{
			closedir(opendir(main->exec->cmd[0]));
			free_and_exit_error(main, NULL, "Is a directory", 126);
		}
		if (access(main->exec->cmd[0], F_OK) != 0)
			free_and_exit_error(main, NULL, "No such file or directory", 127);
		if (access(main->exec->cmd[0], X_OK) != 0)
			free_and_exit_error(main, NULL, "Permission denied", 126);
		execve(main->exec->cmd[0], main->exec->cmd, main->envtab);
		execve_err(main, main->envtab, NULL, main->exec->cmd[0]);
	}
	env_path = env_path_finding(main, main->envtab);
	path = get_path(main, env_path, main->envtab);
	if (path == NULL)
	{
		free(path);
		free(env_path);
		execve_err(main, main->envtab, path, main->exec->cmd[0]);
		return ;
	}
	execve(path, main->exec->cmd, main->envtab);
	execve_err(main, main->envtab, path, main->exec->cmd[0]);
}

void	init_simple_cmd(t_main *main)
{
	pid_t	pid;
	int		tmp;

	pid = fork();
	if (pid == -1)
		fork_error(main, ERR_FORK);
	if (pid == 0)
	{
		exit_error_two_close(main, main->std_in, main->std_out);
		exit_error_two_close(main, main->exec->infile.fd,
			main->exec->outfile.fd);
		// if (main->exec->cmd[0][0] == '\0')
		// {
		// 	exit(0);
		// }
		exec_simple_cmd(main);
	}
	while (waitpid(pid, &tmp, 0) > 0)
		;
	if (WIFEXITED(tmp) && WEXITSTATUS(tmp) == 127)
		main->errcode = 127;
	if (WIFEXITED(tmp) && WEXITSTATUS(tmp) == 1)
		main->errcode = 1;
	if (WIFEXITED(tmp) && WEXITSTATUS(tmp) == 0)
		main->errcode = 0;
	if (WIFEXITED(tmp) && WEXITSTATUS(tmp) == 126)
		main->errcode = 126;
	if (WIFEXITED(tmp) && WEXITSTATUS(tmp) == 2)
		main->errcode = 2;
}
