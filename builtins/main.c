/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:22:17 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/19 18:41:52 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/main.h"
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
	printf("before readline\n");
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			printf("exit\n");
		if (line[0] != '\0')
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
