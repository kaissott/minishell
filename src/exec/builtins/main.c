/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:22:17 by kaissramire       #+#    #+#             */
/*   Updated: 2025/07/04 20:08:45 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <errno.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

bool	exec_cmd(t_main *main, char **cmd, bool simple)
{
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && ft_strlen(cmd[0]) == 4)
		return (mini_echo(main, cmd));
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0 && ft_strlen(cmd[0]) == 3)
		return (pwd(main));
	else if (ft_strncmp(cmd[0], "env", 3) == 0 && ft_strlen(cmd[0]) == 3)
		return (env_print(main, cmd));
	else if (ft_strncmp(cmd[0], "cd", 2) == 0 && ft_strlen(cmd[0]) == 2)
		return (mini_cd(main->exec->cmd, main));
	else if (ft_strncmp(cmd[0], "exit", 4) == 0 && ft_strlen(cmd[0]) == 4)
		return (mini_exit(main->exec->cmd, main));
	else if (ft_strncmp(cmd[0], "export", 6) == 0 && ft_strlen(cmd[0]) == 6)
		return (mini_export(main));
	else if (ft_strncmp(cmd[0], "unset", 5) == 0 && ft_strlen(cmd[0]) == 5)
		return (mini_unset(main));
	else if (simple == true)
		init_simple_cmd(main);
	return (false);
}

void	reset_struct(char *rl, t_main *main)
{
	int	i;

	if (rl)
		free(rl);
	if (main->exec)
	{
		free_node(main);
	}
}

int	check_input(t_main *main)
{
	t_exec	*node;
	int		fd_out;
	int		fd_in;

	node = main->exec;
	if (node == NULL || (node->cmd == NULL && node->next == NULL))
	{
		if (main->errcode != 0)
			main->errcode = 2;
		return (-1);
	}
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
