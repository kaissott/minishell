/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:46:18 by karamire          #+#    #+#             */
/*   Updated: 2025/07/22 20:58:44 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*path_finding(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path = ft_strdup(ft_strnstr(env[i], "PATH=", 5));
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*cmd_path(char **cmd, char *linktopath)
{
	int		i;
	char	*path;
	char	**path_poss;

	i = 0;
	if (linktopath == NULL)
		return (NULL);
	path_poss = ft_split_slash(linktopath, ':');
	if (path_poss == NULL)
		return (NULL);
	while (path_poss[i] != NULL)
	{
		path = ft_strjoin(path_poss[i], cmd[0]);
		if (path != NULL && (access(path, X_OK) == 0))
		{
			free_tab_2(path_poss);
			return (path);
		}
		if (path)
			free(path);
		path = NULL;
		i++;
	}
	free_tab_2(path_poss);
	return (NULL);
}

int	do_cmd(t_main *main, char **cmd, char **env)
{
	char	*path;
	char	*env_path;

	path = NULL;
	if (exec_cmd(main, cmd, false) == true)
	{
		free_and_exit_error(main, NULL, NULL, 0);
	}
	if (cmd == NULL)
		error_exit("Command not found.", 127, -1);
	ultimate_path_check(main, cmd);
	env_path = env_path_finding(main, main->env_tab);
	path = cmd_path(cmd, env_path);
	if (path == NULL)
	{
		if (!env_path && check_current_dir_exec(main, cmd))
			return (-1);
		free(path);
		free(env_path);
		execve_err(main, main->env_tab, path, main->exec->cmd[0]);
		return (-1);
	}
	execve(path, cmd, env);
	execve_err(main, env, path, cmd[0]);
	return (-1);
}

void	close_fd(int prev_fd, int outfile, int if_hd)
{
	if (if_hd == 2)
	{
		if (unlink("here_doc") == -1)
			perror("Unlink here_doc error : ");
	}
	if (prev_fd != -1)
		close(prev_fd);
	if (outfile != -1)
		close(outfile);
}

void	access_out_check(char *out, int prev_fd, int outfile)
{
	if (access(out, W_OK) == -1)
	{
		while (wait(NULL) > 0)
			;
		close_fd(prev_fd, outfile, -1);
		ft_putendl_fd("Permission Denied", 2);
		exit(1);
	}
}
