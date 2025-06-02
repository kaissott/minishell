/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:22:17 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/02 18:20:12 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include <errno.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

bool	exec_cmd(t_main *main, int fd)
{
	char	**cmd;

	cmd = main->node->cmd;
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && ft_strlen(cmd[0]) == 4)
		mini_echo(main);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0 && ft_strlen(cmd[0]) == 3)
		pwd(main);
	else if (ft_strncmp(cmd[0], "env", 3) == 0 && ft_strlen(cmd[0]) == 3)
		env_print(main);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0 && ft_strlen(cmd[0]) == 2)
		mini_cd(main->node->cmd, main);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0 && ft_strlen(cmd[0]) == 4)
		mini_exit(main->node->cmd, main);
	else if (ft_strncmp(cmd[0], "export", 6) == 0 && ft_strlen(cmd[0]) == 6)
		mini_export(main);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0 && ft_strlen(cmd[0]) == 5)
		mini_unset(main);
	else
		init_simple_cmd(main);
	// free_tabs(cmd, NULL);
	return (0);
}

int	check_input(t_main *main)
{
	t_lst_node	*node;
	int			fd_out;
	int			fd_in;

	node = main->node;
	if (node->next == NULL)
	{
		fd_in = main->node->infile.fd;
		fd_out = main->node->outfile.fd;
		file_dup(fd_in, fd_out);
		exec_cmd(main, fd_out);
		close(fd_in);
		close(fd_out);
	}
	else
		pipe_exec(main);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_main	*main;
	t_env	*mainenv;
	int		std_out;
	int		std_in;
	int		i;

	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDERR_FILENO);
	main = malloc(sizeof(t_main));
	check_env_available(env, main);
	while (1)
	{
		i = 0;
		dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
		line = readline("minishell$ ");
		if (!line)
			printf("exit\n");
		if (line[0] != '\0')
			add_history(line);
		create_node(main, line);
		check_input(main);
		while (main->node->cmd[i])
		{
			free(main->node->cmd[i]);
			i++;
		}
		free(main->node->cmd);
		free(line);
		close(main->node->infile.fd);
		close(main->node->outfile.fd);
	}
	sleep(30);
	return (0);
}
