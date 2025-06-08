#include "../../includes/minishell.h"

static ssize_t	extract_quoted_part(t_error *error, t_word_part **parts,
		char *cmd, char quote)
{
	size_t	len;

	len = 1;
	while (cmd[len] && cmd[len] != quote)
		len++;
	if (!cmd[len])
	{
		if (quote == '"')
			set_error(error, ERR_MISSING_DOUBLE_QUOTE, '"');
		else
			set_error(error, ERR_MISSING_SINGLE_QUOTE, '\'');
		return (-1);
	}
	if (len == 1)
		return (2);
	if (create_and_add_word_part(parts, &cmd[1], len - 1, quote) != ERR_NONE)
		return (-1);
	return (len + 1);
}

static ssize_t	extract_unquoted_part(t_word_part **parts, char *cmd)
{
	size_t	len;

	len = 0;
	while (cmd[len] && cmd[len] != ' ' && cmd[len] != '"' && cmd[len] != '\''
		&& !is_operator(&cmd[len]))
		len++;
	if (create_and_add_word_part(parts, cmd, len, '\0') != ERR_NONE)
		return (-1);
	return (len);
}

static ssize_t	extract_word_token(t_token **token_lst, t_error *error,
		char *cmd)
{
	ssize_t	i;
	ssize_t	part_len;
	t_token	*new_token;

	i = 0;
	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (-1);
	while (cmd[i] && cmd[i] != ' ' && !is_operator(&cmd[i]))
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			part_len = extract_quoted_part(error, &new_token->parts, &cmd[i],
					cmd[i]);
		else
			part_len = extract_unquoted_part(&new_token->parts, &cmd[i]);
		if (part_len <= 0)
		{
			free_token_lst(&new_token);
			return (-1);
		}
		i += part_len;
	}
	if (token_lst_add_token_parts(token_lst, new_token) != ERR_NONE)
		return (-1);
	return (i);
}

static ssize_t	extract_operator_token(t_token **token_lst, t_error *error,
		char *cmd)
{
	ssize_t			len;
	t_token_type	token_type;

	len = 1;
	token_type = get_token_type(error, cmd);
	if (token_type == T_ERROR)
		return (-1);
	if (token_type == T_HEREDOC || token_type == T_REDIR_APPEND)
		len = 2;
	if (token_lst_add_node(token_lst, cmd, len, token_type) != ERR_NONE)
	{
		set_error(error, ERR_MALLOC, '\0');
		return (-1);
	}
	return (len);
}

t_parse_error	tokenisation(t_token **token_lst, t_error *error, char *cmd)
{
	ssize_t	i;
	ssize_t	token_len;

	i = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ')
			i++;
		if (!cmd[i])
			break ;
		if (is_operator(&cmd[i]))
			token_len = extract_operator_token(token_lst, error, &cmd[i]);
		else
			token_len = extract_word_token(token_lst, error, &cmd[i]);
		if (token_len <= 0 || error->error_type != ERR_NONE)
		{
			free_token_lst(token_lst);
			return (error->error_type);
		}
		i += token_len;
	}
	return (ERR_NONE);
}
