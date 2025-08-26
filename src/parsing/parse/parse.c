/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:29:33 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/26 19:06:13 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exec	*handle_pipe(t_shell *shell, t_token *token, t_exec *new_cmd,
		bool is_last)
{
	if (!is_last)
	{
		token_lst_delone(&shell->token, token);
		shell->errcode = 0;
		shell->error.error_type = 0;
		shell->error.ambiguous_redir = NULL;
		return (new_cmd->next);
	}
	else
		return (NULL);
}

static t_parse_error	handle_redirection(t_shell *shell, t_token *token,
		t_exec *new_cmd)
{
	t_parse_error	errcode;

	if (token->type == T_REDIR_IN)
		errcode = check_std_cmd(STDIN_FILENO, new_cmd);
	else
		errcode = check_std_cmd(STDOUT_FILENO, new_cmd);
	if (errcode == ERR_NONE)
	{
		if (token->type == T_REDIR_IN)
			process_exec_std(shell, token, new_cmd, STDIN_FILENO);
		else
			process_exec_std(shell, token, new_cmd, STDOUT_FILENO);
	}
	if (errcode != ERR_NONE && errcode != ERR_PREV_OPEN)
		return (errcode);
	token_lst_delone(&shell->token, token->next);
	token_lst_delone(&shell->token, token);
	return (ERR_NONE);
}

static t_parse_error	handle_heredoc(t_shell *shell, t_token *token,
		t_exec *new_cmd)
{
	token_lst_delone(&shell->token, token->next);
	token_lst_delone(&shell->token, token);
	if (new_cmd->infile.fd == -1 || new_cmd->outfile.fd == -1)
		return (secure_close(&new_cmd->infile.fd_heredoc, STDIN_FILENO));
	new_cmd->infile.fd = new_cmd->infile.fd_heredoc;
	return (ERR_NONE);
}

static t_parse_error	handle_token(t_shell *shell, t_token *token,
		t_exec *new_cmd)
{
	if (token->type == T_WORD)
	{
		new_cmd->cmd = resize_cmd_args(new_cmd->cmd, token->value);
		if (!new_cmd->cmd)
			return (ERR_MALLOC);
		token_lst_delone(&shell->token, token);
		return (ERR_NONE);
	}
	else if (token->type >= T_REDIR_IN && token->type <= T_HEREDOC)
	{
		if (token->type == T_HEREDOC)
			return (handle_heredoc(shell, token, new_cmd));
		else
			return (handle_redirection(shell, token, new_cmd));
	}
	return (ERR_TOKEN);
}

t_parse_error	parsing(t_shell *shell)
{
	t_exec			*new_cmd;
	t_parse_error	errcode;

	new_cmd = shell->exec;
	while (shell->token)
	{
		if (shell->token->type == T_PIPE)
		{
			new_cmd = handle_pipe(shell, shell->token, new_cmd, false);
			continue ;
		}
		errcode = handle_token(shell, shell->token, new_cmd);
		if (errcode != ERR_NONE)
			return (errcode);
	}
	handle_pipe(shell, shell->token, new_cmd, true);
	return (ERR_NONE);
}
