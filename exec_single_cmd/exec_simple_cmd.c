/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:40:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/26 17:14:34 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

char	*get_path(t_main *main, char *env_path)
{
	char	**final_env_path;
	char	**cmd;
	char	*final_path;
	int		i;

	i = 0;
	cmd = ft_split(main->node->cmd, ' ');
	final_env_path = ft_split_slash(env_path, ':');
	while (final_env_path[i] != NULL)
	{
		final_path = ft_strjoin(final_env_path[i], cmd[0]);
		if (final_path != NULL && (access(final_path, X_OK) == 0))
		{
			free_tabs(cmd, final_env_path);
			return (final_path);
		}
		free(final_path);
		final_path = NULL;
		i++;
	}
	return (NULL);
}

char	*env_path_finding(t_main *main)
{
	char	*env_path;
	char	**env;
	int		i;

	i = 0;
	env = main->mainenv;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			env_path = ft_strdup(env[i]); // a gerer
			return (env_path);
		}
		i++;
	}
	return (NULL);
}
void	exec_simple_cmd(t_main *main, int fd_in, int fd_out)
{
	char	**args;
	char	*env_path;
	char	*path;

	args = ft_split(main->node->cmd, ' '); // a gerer
	env_path = env_path_finding(main);
	path = get_path(main, env_path);
	execve(path, args, main->mainenv);
	// error a gerer si execve ne fonctionne pas
}

void	file_dup(int fd_in, int fd_out)
{
	if (fd_in != 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			printf("sheesh");
		close(fd_in);
	}
	if (fd_out != 1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			printf("sheesh2");
		close(fd_out);
	}
}

int	get_outfile_simple_cmd(t_main *main)
{
	int			fd_out;
	t_lst_node	*temp;

	temp = main->node;
	if (temp->outfile.filename != NULL)
	{
		if (temp->outfile.type == T_REDIR_APPEND)
			fd_out = open(temp->outfile.filename, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else if (temp->outfile.type == T_REDIR_TRUNC)
			fd_out = open(temp->outfile.filename, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (fd_out == -1)
			return (fd_out);
	}
	else
		return (1);
}

int	get_infile_simple_cmd(t_main *main)
{
	int			fd_in;
	t_lst_node	*temp;

	temp = main->node;
	if (temp->infile.filename != NULL)
	{
		fd_in = open(temp->infile.filename, O_RDONLY);
		if (fd_in < 0)
			dprintf(2, "infile crash\n");
		return (fd_in);
	}
	else
		return (0);
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
	{
		fd_in = get_infile_simple_cmd(main);
		fd_out = get_outfile_simple_cmd(main);
		file_dup(fd_in, fd_out);
		exec_simple_cmd(main, fd_in, fd_out);
	}
	wait(NULL);
}
/*
	Il faut gerer tout les retours d'erreurs ici.
	FAIRE ATTENTION A QUELLE FONCTION DOIT RETURN ET QUELLE FONCTION DOIT EXIT
	Il faut aussi commencer a discuter si les builtins hors exit doivent etre gerer ici.
	je pense qu'il vaut mieux gerer les infiles et outfiles pour les outputs directement dans la partie builtins mais cela pose probleme pour le cote pipe.
*/
