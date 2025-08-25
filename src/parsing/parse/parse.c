/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:29:33 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/25 21:53:11 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exec	*handle_pipe(t_shell *shell, t_token *token, t_exec *new_cmd,
		bool is_last)
{
	if (new_cmd)
		exec_lst_add_back(&shell->exec, new_cmd);
	if (!is_last)
	{
		token_lst_delone(&shell->token, token);
		shell->errcode = 0;
		shell->error.error_type = 0;
		shell->error.ambiguous_redir = NULL;
		return (create_exec_cmd());
	}
	else
		return (NULL);
}

static t_parse_error	handle_redirection(t_shell *shell, t_token *token,
		t_exec *new_cmd)
{
	int				std;
	t_parse_error	errcode;

	std = STDOUT_FILENO;
	if (token->type == T_REDIR_IN)
	{
		std = STDIN_FILENO;
		new_cmd->infile.type = token->type;
	}
	else
		new_cmd->outfile.type = token->type;
	errcode = check_std_cmd(std, new_cmd);
	if (errcode == ERR_NONE)
	{
		errcode = process_exec_std(shell, token, new_cmd, std);
		if (errcode != ERR_NONE && errcode != ERR_AMBIGUOUS_REDIR)
			return (errcode);
	}
	else if (errcode != ERR_PREV_OPEN)
		return (errcode);
	token_lst_delone(&shell->token, token->next);
	token_lst_delone(&shell->token, token);
	return (ERR_NONE);
}

static t_parse_error	handle_heredoc(t_shell *shell, t_token *token,
		t_exec *new_cmd)
{
	t_parse_error	errcode;
	int				pipefd[2];

	if (secure_close(&new_cmd->fd_heredoc) != ERR_NONE)
		return (ERR_CLOSE);
	// return (ERR_PIPE);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (ERR_PIPE);
	}
	new_cmd->fd_heredoc = pipefd[0];
	errcode = handle_in_heredoc(new_cmd, &pipefd[1], token->next->value);
	return (errcode);
}

static t_parse_error	handle_token(t_shell *shell, t_token *token,
		t_exec *new_cmd)
{
	t_parse_error	errcode;

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
		{
			errcode = check_std_cmd(STDIN_FILENO, new_cmd);
			// printf("errcode after check in T_HD : %d\n", errcode);
			if (errcode == ERR_NONE)
				new_cmd->infile.fd = new_cmd->fd_heredoc;
			token_lst_delone(&shell->token, token->next);
			token_lst_delone(&shell->token, token);
			if (errcode == ERR_PREV_OPEN)
				return (ERR_NONE);
			return (errcode);
		}
		else
			return (handle_redirection(shell, token, new_cmd));
	}
	return (ERR_TOKEN);
}

t_parse_error	process_heredocs(t_shell *shell, t_exec *new_cmd)
{
	t_token			*tok;
	t_parse_error	err;

	tok = shell->token;
	while (tok)
	{
		if (tok->type == T_PIPE)
			break ;
		if (tok->type == T_HEREDOC)
		{
			if (new_cmd->fd_heredoc == -1)
				return (ERR_PREV_OPEN);
			err = handle_heredoc(shell, tok, new_cmd);
			if (err != ERR_NONE)
				return (err);
			tok = tok->next->next;
			continue ;
		}
		tok = tok->next;
	}
	return (ERR_NONE);
}

static t_parse_error	parse_tokens(t_shell *shell, t_exec *new_cmd)
{
	t_parse_error	errcode;

	while (shell->token)
	{
		if (shell->token->type == T_PIPE)
		{
			new_cmd = handle_pipe(shell, shell->token, new_cmd, false);
			if (!new_cmd)
				return (ERR_MALLOC);
			errcode = process_heredocs(shell, new_cmd);
			if (errcode != ERR_NONE)
				return (errcode);
			continue ;
		}
		errcode = handle_token(shell, shell->token, new_cmd);
		if (errcode != ERR_NONE)
		{
			free_exec(new_cmd);
			return (errcode);
		}
	}
	handle_pipe(shell, shell->token, new_cmd, true);
	// printf("finish parse\n");
	// print_exec_lst(&shell->exec, "EXEC LST finish :\n");
	// print_token_lst(&shell->token, "TOKEN LST finish :\n");
	return (ERR_NONE);
}

t_parse_error	parsing(t_shell *shell)
{
	t_exec			*new_cmd;
	t_parse_error	errcode;

	new_cmd = create_exec_cmd();
	if (!new_cmd)
		return (ERR_MALLOC);
	errcode = process_heredocs(shell, new_cmd);
	if (errcode != ERR_NONE)
		return (errcode);
	// printf("first process ok\n");
	return (parse_tokens(shell, new_cmd));
}

// t_parse_error	parsing(t_shell *shell)
// {
// 	t_exec			*new_cmd;
// 	t_parse_error	errcode;

// 	new_cmd = create_exec_cmd();
// 	if (!new_cmd)
// 		return (ERR_MALLOC);
// 	while (shell->token)
// 	{
// 		if (shell->token->type == T_PIPE)
// 		{
// 			new_cmd = handle_pipe(shell, shell->token, new_cmd, false);
// 			if (!new_cmd)
// 				return (ERR_MALLOC);
// 			continue ;
// 		}
// 		errcode = handle_token(shell, shell->token, new_cmd);
// 		if (errcode != ERR_NONE)
// 		{
// 			free_exec(new_cmd);
// 			return (errcode);
// 		}
// 	}
// 	handle_pipe(shell, shell->token, new_cmd, true);
// 	return (ERR_NONE);
// }
