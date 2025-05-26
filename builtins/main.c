/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:22:17 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/26 17:18:20 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include <errno.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

bool	is_a_builtins(t_main *main, bool file)
{
	int		fd;
	bool	tmp;
	char	**cmd;

	tmp = false;
	fd = 1;
	if (file == true)
		fd = get_outfile_simple_cmd(main);
	if (ft_strncmp(main->node->cmd, "echo", 4) == 0
		&& main->node->cmd[4] == ' ')
		tmp = mini_echo(main);
	if (ft_strncmp(main->node->cmd, "pwd", 3) == 0 && main->node->cmd[3] == ' ')
		tmp = pwd(main);
	if (ft_strncmp(main->node->cmd, "env", 3) == 0 && main->node->cmd[3] == ' ')
		tmp = env_print(main);
	if (ft_strncmp(main->node->cmd, "cd", 2) == 0 && main->node->cmd[2] == ' ')
		tmp = mini_cd(main->node->cmd, main);
	return (true);
}

int	exec_single_cmd(t_main *main)
{
	if (is_a_builtins(main, true) == false)
		init_simple_cmd(main);
	return (0);
}
int	check_input(t_main *main)
{
	t_lst_node	*node;

	node = main->node;
	if (node->next == NULL)
		exec_single_cmd(main);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_main		*main;
	t_lst_node	*node;

	(void)ac;
	(void)av;
	main = malloc(sizeof(t_main));
	node = malloc(sizeof(t_lst_node));
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			printf("exit\n");
		if (line[0] != '\0')
			add_history(line);
		main->mainenv = env;
		main->node = node;
		main->node->cmd = line;
		main->node->infile.filename = NULL;
		main->node->outfile.filename = "test";
		main->node->outfile.type = T_REDIR_TRUNC;
		exec_single_cmd(main);
		free(line);
	}
	sleep(30);
	return (0);
}
