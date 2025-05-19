/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:23:49 by karamire          #+#    #+#             */
/*   Updated: 2025/04/04 16:11:35 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*cmd_path(char *cmd, char *linktopath)
{
	int		i;
	char	*path;
	char	**path_poss;
	char	**cmd_tab;

	i = 0;
	cmd_tab = ft_split(cmd, ' ');
	path_poss = ft_split_slash(linktopath, ':');
	free(linktopath);
	if (cmd_tab == NULL || path_poss == NULL)
		return (free_tab(cmd_tab, path_poss));
	while (path_poss[i] != NULL)
	{
		path = ft_strjoin(path_poss[i], cmd_tab[0]);
		if (path != NULL && (access(path, X_OK) == 0))
		{
			free_tab(cmd_tab, path_poss);
			return (path);
		}
		free(path);
		path = NULL;
		i++;
	}
	return (free_tab(cmd_tab, path_poss));
}

int	do_cmd(char *cmd, char **env)
{
	char	**cmdtab;
	char	*path;

	cmdtab = ft_split(cmd, ' ');
	if (cmdtab == NULL)
		error_exit("Command not found.", 127, -1);
	if (strrchr_slash(cmdtab[0], '/'))
		execve(cmdtab[0], cmdtab, env);
	else
	{
		path = cmd_path(cmd, path_finding(env));
		if (path == NULL)
		{
			error_exec(cmdtab, cmdtab[0]);
			return (-1);
		}
		execve(path, cmdtab, env);
	}
	error_exec(cmdtab, cmdtab[0]);
	return (-1);
}

void	close_fd(int prev_fd, int outfile)
{
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
		close_fd(prev_fd, outfile);
		ft_putendl_fd("Permission Denied", 2);
		exit(1);
	}
}
