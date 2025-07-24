/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:22:17 by karamire          #+#    #+#             */
/*   Updated: 2025/07/24 23:06:48 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

bool	exec_cmd(t_shell *main, char **cmd, bool simple)
{
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && ft_strlen(cmd[0]) == 4)
		return (mini_echo(main, cmd));
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0 && ft_strlen(cmd[0]) == 3)
		return (pwd(main));
	else if (ft_strncmp(cmd[0], "env", 3) == 0 && ft_strlen(cmd[0]) == 3)
		return (env_print(main, cmd));
	else if (ft_strncmp(cmd[0], "cd", 2) == 0 && ft_strlen(cmd[0]) == 2)
		return (mini_cd(cmd, main));
	else if (ft_strncmp(cmd[0], "exit", 4) == 0 && ft_strlen(cmd[0]) == 4)
		return (mini_exit(cmd, main));
	else if (ft_strncmp(cmd[0], "export", 6) == 0 && ft_strlen(cmd[0]) == 6)
		return (mini_export(main, cmd));
	else if (ft_strncmp(cmd[0], "unset", 5) == 0 && ft_strlen(cmd[0]) == 5)
		return (mini_unset(main, cmd));
	else if (simple == true)
		init_simple_cmd(main);
	return (false);
}

void	reset_struct(char *rl, t_shell *main)
{
	if (rl)
		free(rl);
	if (main->exec)
		free_node(main);
}

bool	node_check(t_shell *main)
{
	t_exec	*node;

	node = main->exec;
	if (node == NULL)
	{
		if (main->errcode != 0)
			main->errcode = 2;
		close_node(main);
		return (false);
	}
	else if (node->cmd == NULL && node->next == NULL)
	{
		if (node->infile.fd == -1 || node->outfile.fd == -1)
			main->errcode = 1;
		else
			main->errcode = 0;
		close_node(main);
		return (false);
	}
	return (true);
}

int	check_input(t_shell *main)
{
	t_exec	*node;
	int		fd_out;
	int		fd_in;

	node = main->exec;
	if (node_check(main) == false)
		return (-1);
	if (node->next == NULL)
	{
		fd_in = main->exec->infile.fd;
		fd_out = main->exec->outfile.fd;
		if (file_dup(main, fd_in, fd_out) == 0)
			exec_cmd(main, node->cmd, true);
		close_node(main);
	}
	else
		pipe_exec(main);
	return (0);
}
