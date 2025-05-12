/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:22:17 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/13 00:31:06 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/builtins.h"
#include "include/main.h"
#include <errno.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*mainenv;
	t_main	*main;

	(void)ac;
	(void)av;
	main = malloc(sizeof(t_main));
	mainenv = env_build(env);
	main->mainenv = mainenv;
	printf("%s\n", mainenv->env);
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		if (ft_strncmp("exit", line, 4) == 0)
			mini_exit(line, main);
		if (ft_strncmp("pwd", line, 3) == 0)
			pwd();
		if (ft_strncmp("echo", line, 4) == 0)
			mini_echo(line);
		if (ft_strncmp("cd", line, 2) == 0)
			mini_cd(line, main);
		if (ft_strncmp("env", line, 3) == 0)
			env_print(main->mainenv);
		free(line);
	}
	sleep(30);
	return (0);
}
