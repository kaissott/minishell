#include "../../includes/minishell.h"

int	is_operator(const char *str)
{
	return (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)
		|| str[0] == '|' || str[0] == '>' || str[0] == '<');
}

t_token_type	get_token_type(char *cmd)
{
	if (cmd[0] == '|')
	{
		if (cmd[1] == '|')
			return (T_DOUBLE_PIPE_ERROR);
		return (T_PIPE);
	}
	else if (cmd[0] == '<')
	{
		if (cmd[1] == '<')
			return (T_HEREDOC);
		return (T_REDIR_IN);
	}
	else if (cmd[0] == '>')
	{
		if (cmd[1] == '>')
			return (T_REDIR_APPEND);
		return (T_REDIR_TRUNC);
	}
	else
		return (T_STRING);
}

ssize_t	create_token_node(t_token **lst_token, const char *cmd,
		const ssize_t len, t_token_type type)
{
	t_token	*token_node;
	char	*value;

	value = ft_substr(cmd, 0, len);
	if (!value)
		return (-1);
	token_node = lst_create_node(value, type);
	if (!token_node)
	{
		free(value);
		return (-1);
	}
	lst_add_back(lst_token, token_node);
	return (1);
}

ssize_t	get_operator_token(t_token **lst_token, char *cmd)
{
	ssize_t			len;
	t_token_type	token_type;

	len = 1;
	token_type = get_token_type(cmd);
	if (token_type < 0)
		return (token_type);
	if (token_type == T_HEREDOC || token_type == T_REDIR_APPEND)
		len = 2;
	if (create_token_node(lst_token, cmd, len, token_type) == -1)
		return (-1);
	return (len);
}

void	toggle_quote_state(char quote_char, bool *in_double_quote,
		bool *in_single_quote)
{
	if (quote_char == '"' && !*in_single_quote)
		*in_double_quote = !*in_double_quote;
	else if (quote_char == '\'' && !*in_double_quote)
		*in_single_quote = !*in_single_quote;
}
