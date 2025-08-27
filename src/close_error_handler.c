/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_error_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 01:10:44 by karamire          #+#    #+#             */
/*   Updated: 2025/08/27 07:42:07 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_minishell(t_shell *main, int errcode, char *err)
{
	if (main)
	{
		ft_safe_close(&main->std_in, main);
		ft_safe_close(&main->std_out, main);
		close_node(main);
		free_struct(main);
		if (main)
			free(main);
	}
	ft_putendl_fd(err, 2);
	rl_clear_history();
	exit(errcode);
}

void	exit_error_two_close(t_shell *main, int *fd1, int *fd2)
{
	if (*fd1 > 1)
	{
		ft_safe_close(fd1, main);
	}
	if (*fd2 > 1)
	{
		ft_safe_close(fd2, main);
	}
}

void	free_shell_error(t_shell *shell)
{
	if (shell->token)
		free_token_lst(&shell->token);
	if (shell->exec)
		free_exec_lst(&shell->exec);
	shell->error.error_type = ERR_NONE;
	shell->error.unexpected_token = '\0';
	shell->error.ambiguous_redir = NULL;
}
