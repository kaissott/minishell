/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:22:17 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/10 17:21:09 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	(void)ac;
	(void)av;
	(void)env;
	(void)mainenv;
	while (1)
	{
		line = readline("minishell$ ");
		if (*line)
			add_history(line);
		if (ft_strncmp("exit", line, 4) == 0)
			mini_exit(line);
		if (ft_strncmp("pwd", line, 3) == 0)
			pwd();
		if (ft_strncmp("echo", line, 4) == 0)
			mini_echo(line);
		free(line);
	}
	return (0);
}
