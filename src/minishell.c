/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:03:36 by luca              #+#    #+#             */
/*   Updated: 2025/04/28 18:15:26 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_shell(void)
{
	char	*rl;

	while (1)
	{
		rl = readline("$> ");
		if (*rl)
			add_history(rl);
		free(rl);
		rl_on_new_line();
	}
	clear_history();
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	start_shell();
	return (EXIT_SUCCESS);
}
