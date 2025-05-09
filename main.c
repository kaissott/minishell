/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:22:17 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/09 02:37:31 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/main.h"
#include <errno.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		printf("%d", errno);
		if (*line)
			add_history(line);
		if (ft_strncmp("exit", line, 4) == 0)
			mini_exit(line);
		free(line);
	}
	return (0);
}
