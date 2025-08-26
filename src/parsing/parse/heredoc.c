/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 22:52:01 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/26 09:13:01 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exec	*handle_pipe(t_shell *shell, t_exec *new_cmd, bool at_end)
{
	exec_lst_add_back(&shell->exec, new_cmd);
	if (at_end)
		return (NULL);
	return (create_exec_cmd());
}

static t_parse_error	handle_heredoc(t_token *token, t_exec *new_cmd)
{
	t_parse_error	errcode;
	int				pipefd[2];

	if (secure_close(&new_cmd->infile.fd_heredoc, STDIN_FILENO) != ERR_NONE)
		return (ERR_CLOSE);
	if (pipe(pipefd) == -1)
	{
		print_perror("pipe");
		return (ERR_PIPE);
	}
	new_cmd->infile.fd_heredoc = pipefd[0];
	errcode = handle_in_heredoc(new_cmd, &pipefd[1], token->next->value);
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
			new_cmd = handle_pipe(shell, new_cmd, false);
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
	handle_pipe(shell, new_cmd, true);
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
