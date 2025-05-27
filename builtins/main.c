/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:22:17 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/27 19:42:38 by karamire         ###   ########.fr       */
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

	cmd = ft_split(main->node->cmd, ' ');
	if (ft_strncmp(cmd[0], "echo", 4) == 0 && ft_strlen(cmd[0]) == 4)
		mini_echo(main);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0 && ft_strlen(cmd[0]) == 3)
		pwd(main, fd);
	else if (ft_strncmp(cmd[0], "env", 3) == 0 && ft_strlen(cmd[0]) == 3)
		env_print(main, fd);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0 && ft_strlen(cmd[0]) == 2)
		mini_cd(main->node->cmd, main);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0 && ft_strlen(cmd[0]) == 4)
		mini_exit(main->node->cmd, main);
	else
	{
		printf("caca");
		init_simple_cmd(main);
	}
	free_tabs(cmd, NULL);
	if (fd > 1)
		close(fd);
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
		fd_in = get_infile_simple_cmd(main);
		fd_out = get_outfile_simple_cmd(main);
		file_dup(fd_in, fd_out);
		exec_cmd(main, fd_out);
		close(fd_in);
		close(fd_out);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_main		*main;
	t_env		*mainenv;
	t_lst_node	*node;
	int			std_out;
	int			std_in;

	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDERR_FILENO);
	main = malloc(sizeof(t_main));
	node = malloc(sizeof(t_lst_node));
	mainenv = env_build(env);
	while (1)
	{
		dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
		line = readline("minishell$ ");
		if (!line)
			printf("exit\n");
		if (line[0] != '\0')
			add_history(line);
		main->mainenv = mainenv;
		main->node = node;
		main->node->cmd = line;
		main->node->infile.filename = NULL;
		main->node->outfile.filename = "ENV";
		main->node->outfile.type = T_REDIR_TRUNC;
		main->node->next = NULL;
		check_input(main);
		free(line);
	}
	sleep(30);
	return (0);
}
