/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:40:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/16 00:17:11 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path(t_main *main, char *env_path)
{
	char	**final_env_path;
	char	**cmd;
	char	*final_path;
	int		i;

	i = 0;
	cmd = main->exec->cmd;
	final_env_path = ft_split_slash(env_path, ':');
	while (final_env_path[i] != NULL)
	{
		final_path = ft_strjoin(final_env_path[i], cmd[0]);
		if (!final_path)
			free_and_exit_error(main, NULL, ERR_MALLOC, 12);
		if ((access(final_path, X_OK) == 0))
		{
			free_tabs(NULL, final_env_path);
			return (final_path);
		}
		free(final_path);
		final_path = NULL;
		i++;
	}
	free_tabs(NULL, final_env_path);
	return (NULL);
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
			return (env_path);
		}
		i++;
	}
	return (NULL);
}
void	exec_simple_cmd(t_main *main, int fd_in, int fd_out)
{
	char	*env_path;
	char	*path;
	char	**env;

	env = env_to_tab(main);
	if (strrchr_slash(main->exec->cmd[0], '/'))
		execve(main->exec->cmd[0], main->exec->cmd, env);
	env_path = env_path_finding(main, env);
	path = get_path(main, env_path);
	if (path == NULL)
	{
		free(env_path);
		free(path);
		free(env);
		return;
	}
	execve(path, main->exec->cmd, env);
}

void	file_dup(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			printf("sheesh");
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			printf("sheesh2");
		close(fd_out);
	}
}

void	init_simple_cmd(t_main *main)
{
	int		fd_in;
	int		fd_out;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fork_error(main, ERR_FORK);
	if (pid == 0)
		exec_simple_cmd(main, fd_in, fd_out);
	wait(NULL);
}
/*
	Il faut gerer tout les retours d'erreurs ici.
	FAIRE ATTENTION A QUELLE FONCTION DOIT RETURN ET QUELLE FONCTION DOIT EXIT
	Il faut aussi commencer a discuter si les builtins hors exit doivent etre gerer ici.
	je pense qu'il vaut mieux gerer les infiles et outfiles pour les outputs directement dans la partie builtins mais cela pose probleme pour le cote pipe.
*/
