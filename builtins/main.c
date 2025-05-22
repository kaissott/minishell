/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:22:17 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/23 00:51:09 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include <errno.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

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
		main->node->outfile.filename = NULL;
		main->node->outfile.type = T_REDIR_TRUNC;
		init_simple_cmd(main);
		free(line);
	}
	sleep(30);
	return (0);
}
