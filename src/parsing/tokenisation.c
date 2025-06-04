#include "../../includes/minishell.h"

static ssize_t	extract_quoted_token(t_token **lst_token, t_error *error,
		char *cmd)
{
	ssize_t	len;
	bool	in_squote;
	bool	in_dquote;

	len = 1;
	in_squote = false;
	in_dquote = false;
	toggle_quote_state(cmd[0], &in_dquote, &in_squote);
	while (cmd[len] && cmd[len] != cmd[0])
		len++;
	if (cmd[len] == cmd[0] && len > 1)
	{
		toggle_quote_state(cmd[0], &in_dquote, &in_squote);
		len++;
		if (lst_token_add_node(lst_token, &cmd[1], len - 2,
				get_token_quoted_type(&in_dquote, &in_squote)) == ERR_MALLOC)
		{
			set_error(error, ERR_MALLOC, '\0');
			return (-1);
		}
		return (len);
	}
	else if (len == 1 && cmd[len])
		return (2);
	return (-1);
}

static ssize_t	extract_word_token(t_token **lst_token, t_error *error,
		char *cmd)
{
	ssize_t	len;

	len = 0;
	if (cmd[0] == '"' || cmd[0] == '\'')
		return (extract_quoted_token(lst_token, error, cmd));
	else
	{
		while (cmd[len] && cmd[len] != ' ' && !is_operator(&cmd[len])
			&& cmd[len] != '"' && cmd[len] != '\'')
			len++;
		if (lst_token_add_node(lst_token, cmd, len, T_WORD) == ERR_MALLOC)
		{
			set_error(error, ERR_MALLOC, '\0');
			return (-1);
		}
		return (len);
	}
}

static ssize_t	extract_operator_token(t_token **lst_token, t_error *error,
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
	if (lst_token_add_node(lst_token, cmd, len, token_type) == ERR_MALLOC)
	{
		set_error(error, ERR_MALLOC, '\0');
		return (-1);
	}
	return (len);
}

t_parse_error	tokenisation(t_token **lst_token, t_error *error, char *cmd)
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
			token_len = extract_operator_token(lst_token, error, &cmd[i]);
		else
			token_len = extract_word_token(lst_token, error, &cmd[i]);
		if (token_len <= 0 || error->error_type != ERR_NONE)
		{
			free_lst_token(lst_token);
			return (error->error_type);
		}
		i += token_len;
	}
	return (ERR_NONE);
}
