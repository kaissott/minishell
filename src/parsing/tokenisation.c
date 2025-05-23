#include "../../includes/minishell.h"

static t_token_type	get_token_quoted_type(bool *in_double_quote,
		bool *in_single_quote)
{
	if (*in_double_quote)
		return (T_ENV_STRING);
	else if (*in_single_quote)
		return (T_STRING);
}

static ssize_t	extract_quoted_token(t_token **lst_token, char *cmd)
{
	ssize_t			len;
	t_token_type	token_type;
	bool			in_single_quote;
	bool			in_double_quote;

	len = 1;
	in_single_quote = false;
	in_double_quote = false;
	toggle_quote_state(cmd[0], &in_double_quote, &in_single_quote);
	token_type = get_token_quoted_type(&in_double_quote, &in_single_quote);
	while (cmd[len] && cmd[len] != cmd[0])
		len++;
	if (cmd[len] == cmd[0] && len > 1)
	{
		toggle_quote_state(cmd[0], &in_double_quote, &in_single_quote);
		len++;
		if (create_token_node(lst_token, &cmd[1], len - 2, token_type) == -1)
			return (-1);
		return (len);
	}
	else if (len == 1 && cmd[len])
		return (2);
	if (in_single_quote)
		return (MISSING_SINGLE_QUOTE);
	return (MISSING_DOUBLE_QUOTE);
}

static ssize_t	extract_word_token(t_token **lst_token, char *cmd)
{
	ssize_t	len;

	len = 0;
	if (cmd[0] == '"' || cmd[0] == '\'')
		return (extract_quoted_token(lst_token, cmd));
	else
	{
		while (cmd[len] && cmd[len] != ' ' && !is_operator(&cmd[len])
			&& cmd[len] != '"' && cmd[len] != '\'')
			len++;
		if (create_token_node(lst_token, cmd, len, T_WORD) == -1)
			return (-1);
		return (len);
	}
}

int	tokenisation(t_token **lst_token, char *cmd)
{
	ssize_t	i;
	ssize_t	token_len;

	i = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ')
			i++;
		if (is_operator(&cmd[i]))
			token_len = get_operator_token(lst_token, &cmd[i]);
		else
			token_len = extract_word_token(lst_token, &cmd[i]);
		if (token_len <= 0)
		{
			free_lst_token(lst_token);
			return ((int)token_len);
		}
		i += token_len;
	}
	return (0);
}

void	parse(t_token **lst_token, char *cmd)
{
	int	process_token;

	process_token = tokenisation(lst_token, cmd);
	if (process_token < 0)
		printf("%s\n", get_token_error_msg(process_token));
	print_lst(*lst_token, "\nToken lst :\n");
}
