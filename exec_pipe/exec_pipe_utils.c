/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:46:18 by karamire          #+#    #+#             */
/*   Updated: 2025/06/02 19:38:21 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:47:07 by karamire          #+#    #+#             */
/*   Updated: 2025/06/02 15:35:59 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

char	*path_finding(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path = ft_strdup(env[i]);
			dprintf(2, "%s\n", path);
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
	path_poss = ft_split_slash(linktopath, ':');
	free(linktopath);
	while (path_poss[i] != NULL)
	{
		path = ft_strjoin(path_poss[i], cmd[0]);
		if (path != NULL && (access(path, X_OK) == 0))
		{
			// free_tab_pipe(cmd, path_poss);
			return (path);
		}
		free(path);
		path = NULL;
		i++;
	}
	return (NULL);
}

int	do_cmd(char **cmd, char **env)
{
	char	*path;

	if (cmd == NULL)
	{
		error_exit("Command not found.", 127, -1);
	}
	if (strrchr_slash(cmd[0], '/'))
		execve(cmd[0], cmd, env);
	else
	{
		path = cmd_path(cmd, path_finding(env));
		if (path == NULL)
		{
			error_exec_b(cmd, cmd[0]);
			return (-1);
		}
		execve(path, cmd, env);
	}
	dprintf(2, "ratata");
	error_exec_b(cmd, cmd[0]);
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

void	access_out_check(char *out, int prev_fd, int outfile, int if_hd)
{
	if (access(out, W_OK) == -1)
	{
		while (wait(NULL) > 0)
			;
		close_fd(prev_fd, outfile, if_hd);
		ft_putendl_fd("Permission Denied", 2);
		exit(1);
	}
}
