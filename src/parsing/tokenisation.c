/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:30:08 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/30 10:29:25 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	extract_quoted_chunk(t_token_chunk **chunks, const char *cmd,
		char quote)
{
	const char	*start;

	start = cmd;
	cmd++;
	while (*cmd && *cmd != quote)
		cmd++;
	if (!*cmd)
	{
		if (quote == '"')
			return (ERR_MISSING_DOUBLE_QUOTE);
		else
			return (ERR_MISSING_SINGLE_QUOTE);
	}
	if (create_and_add_chunk(chunks, start + 1, cmd - start - 1,
			quote) != ERR_NONE)
		return (ERR_MALLOC);
	return ((cmd - start) + 1);
}

static ssize_t	extract_unquoted_chunk(t_token_chunk **chunks, const char *cmd)
{
	const char	*start;

	start = cmd;
	while (*cmd && *cmd != ' ' && *cmd != '\t' && *cmd != '"' && *cmd != '\''
		&& !is_operator(cmd))
		cmd++;
	if (create_and_add_chunk(chunks, start, cmd - start, '\0') != ERR_NONE)
		return (ERR_MALLOC);
	return (cmd - start);
}

static ssize_t	extract_word_token(t_shell *shell, const char *cmd)
{
	const char	*start;
	ssize_t		chunk_len;
	t_token		*new_token;

	start = cmd;
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (ERR_MALLOC);
	while (*cmd && *cmd != ' ' && *cmd != '\t' && !is_operator(cmd))
	{
		if ((*cmd == '"' && *(cmd - 1) != '\\') || (*cmd == '\'' && *(cmd
				- 1) != '\\'))
			chunk_len = extract_quoted_chunk(&new_token->chunks, cmd, *cmd);
		else
			chunk_len = extract_unquoted_chunk(&new_token->chunks, cmd);
		if (chunk_len <= 0)
		{
			free_token(new_token);
			return (chunk_len);
		}
		cmd += chunk_len;
	}
	if (token_lst_add_chunks(shell, new_token) != ERR_NONE)
		return (ERR_MALLOC);
	return (cmd - start);
}

static ssize_t	extract_operator_token(t_shell *shell, const char *cmd,
		bool *begin_with_token)
{
	ssize_t			len;
	t_token_type	token_type;

	len = 1;
	token_type = get_token_type(&shell->error, cmd, *begin_with_token);
	if (token_type == T_ERROR_SYNTAX)
		return (ERR_SYNTAX);
	else if (token_type == T_ERROR_PIPE)
		return (ERR_DOUBLE_PIPE);
	if (token_type == T_HEREDOC || token_type == T_REDIR_APPEND)
		len = 2;
	if (token_lst_add_operator_node(&shell->token, cmd, len,
			token_type) != ERR_NONE)
		return (ERR_MALLOC);
	return (len);
}

t_parse_error	tokenisation(t_shell *shell, const char *cmd)
{
	ssize_t	token_len;
	bool	begin_with_token;

	begin_with_token = true;
	while (*cmd)
	{
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;
		if (!*cmd)
			break ;
		if (is_operator(cmd))
			token_len = extract_operator_token(shell, cmd, &begin_with_token);
		else
		{
			begin_with_token = false;
			token_len = extract_word_token(shell, cmd);
		}
		if (token_len <= 0 || shell->error.error_type != ERR_NONE)
			return (token_len);
		cmd += token_len;
	}
	set_heredocs_delimiters(shell);
	return (ERR_NONE);
}
