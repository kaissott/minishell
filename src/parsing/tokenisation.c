/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:30:08 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 00:26:04 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	extract_quoted_chunk(t_token_chunk **chunks, char *cmd,
		char quote)
{
	ssize_t	len;

	len = 1;
	while (cmd[len] && cmd[len] != quote)
		len++;
	if (!cmd[len])
	{
		if (quote == '"')
			return (ERR_MISSING_DOUBLE_QUOTE);
		else
			return (ERR_MISSING_SINGLE_QUOTE);
	}
	if (create_and_add_chunk(chunks, &cmd[1], len - 1, quote) != ERR_NONE)
		return (ERR_MALLOC);
	return (len + 1);
}

static ssize_t	extract_unquoted_chunk(t_token_chunk **chunks, char *cmd)
{
	ssize_t	len;

	len = 0;
	while (cmd[len] && cmd[len] != ' ' && cmd[len] != '\t' && cmd[len] != '"'
		&& cmd[len] != '\'' && !is_operator(&cmd[len]))
		len++;
	if (create_and_add_chunk(chunks, cmd, len, '\0') != ERR_NONE)
		return (ERR_MALLOC);
	return (len);
}

static ssize_t	extract_word_token(t_main *shell, char *cmd)
{
	ssize_t	i;
	ssize_t	chunk_len;
	t_token	*new_token;

	i = 0;
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (ERR_MALLOC);
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && !is_operator(&cmd[i]))
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			chunk_len = extract_quoted_chunk(&new_token->chunks, &cmd[i],
					cmd[i]);
		else
			chunk_len = extract_unquoted_chunk(&new_token->chunks, &cmd[i]);
		if (chunk_len <= 0)
		{
			free_token(new_token);
			return (chunk_len);
		}
		i += chunk_len;
	}
	if (token_lst_add_chunks(shell, new_token) != ERR_NONE)
		return (ERR_MALLOC);
	return (i);
}

static ssize_t	extract_operator_token(t_main *shell, char *cmd)
{
	ssize_t			len;
	t_token_type	token_type;

	len = 1;
	token_type = get_token_type(&shell->error, cmd);
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

t_parse_error	tokenisation(t_main *shell, char *cmd)
{
	ssize_t	i;
	ssize_t	token_len;

	i = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ' || cmd[i] == '\t')
			i++;
		if (!cmd[i])
			break ;
		if (is_operator(&cmd[i]))
			token_len = extract_operator_token(shell, &cmd[i]);
		else
			token_len = extract_word_token(shell, &cmd[i]);
		if (token_len <= 0 || shell->error.error_type != ERR_NONE)
			return (token_len);
		i += token_len;
	}
	set_heredocs_delimiters(shell);
	return (ERR_NONE);
}
