/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 22:52:01 by ludebion          #+#    #+#             */
/*   Updated: 2025/09/01 21:25:58 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parse_error	write_in_heredoc(t_exec *new_cmd, int *pipe_write,
		char *delimiter)
{
	t_parse_error	errcode;
	char			*rl;
	size_t			bytes_write;

	bytes_write = 0;
	while (1)
	{
		rl = NULL;
		if (isatty(STDIN_FILENO))
			rl = readline("heredoc> ");
		if (g_sig_mode == SIGINT)
		{
			free(rl);
			return (ERR_SIG);
		}
		if (!check_line(rl, delimiter))
			break ;
		errcode = check_heredoc(&bytes_write, rl, new_cmd, pipe_write);
		if (errcode != ERR_NONE)
			return (errcode);
	}
	return (ERR_NONE);
}

static int	rl_hook(void)
{
	return (0);
}

static t_parse_error	handle_heredoc(t_token *token, t_exec *new_cmd)
{
	t_parse_error	errcode;
	int				pipefd[2];

	rl_event_hook = rl_hook;
	rl_catch_signals = 0;
	if (secure_close(&new_cmd->infile.fd_heredoc, STDIN_FILENO) != ERR_NONE)
		return (ERR_CLOSE);
	if (pipe(pipefd) == -1)
	{
		print_perror("pipe");
		return (ERR_PIPE);
	}
	new_cmd->infile.fd_heredoc = pipefd[0];
	init_sigaction_hd();
	errcode = write_in_heredoc(new_cmd, &pipefd[1], token->next->value);
	init_sigaction();
	if (errcode == ERR_SIG)
	{
		if (secure_close(&new_cmd->infile.fd_heredoc, STDIN_FILENO) != ERR_NONE)
			errcode = ERR_CLOSE;
		free_exec(new_cmd);
	}
	if (secure_close(&pipefd[1], STDIN_FILENO) != ERR_NONE)
		return (ERR_CLOSE);
	return (errcode);
}

static t_parse_error	process_heredocs(t_shell *shell, t_exec *new_cmd)
{
	t_parse_error	errcode;
	t_token			*token;

	token = shell->token;
	while (token)
	{
		if (token->type == T_PIPE)
		{
			exec_lst_add_back(&shell->exec, new_cmd);
			new_cmd = create_exec_cmd();
			if (!new_cmd)
				return (ERR_MALLOC);
		}
		if (token->type == T_HEREDOC)
		{
			errcode = handle_heredoc(token, new_cmd);
			if (errcode != ERR_NONE)
				return (errcode);
			token = token->next;
		}
		token = token->next;
	}
	exec_lst_add_back(&shell->exec, new_cmd);
	return (ERR_NONE);
}

t_parse_error	preprocess(t_shell *shell)
{
	t_exec	*new_cmd;

	new_cmd = create_exec_cmd();
	if (!new_cmd)
		return (ERR_MALLOC);
	return (process_heredocs(shell, new_cmd));
}
