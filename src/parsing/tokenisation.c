#include "../../includes/minishell.h"

static ssize_t	extract_quoted_token(t_token **lst_token, char *cmd,
		bool *in_double_quote, bool *in_single_quote)
{
	ssize_t			len;
	char			quote_char;
	t_token_type	token_type;

	len = 1;
	quote_char = cmd[0];
	toggle_quote_state(&quote_char, in_double_quote, in_single_quote);
	if (*in_double_quote)
		token_type = T_ENV_STRING;
	else if (*in_single_quote)
		token_type = T_STRING;
	while (cmd[len] && cmd[len] != quote_char)
		len++;
	if (cmd[len] == quote_char)
	{
		toggle_quote_state(&quote_char, in_double_quote, in_single_quote);
		len++;
		if (create_token_node(lst_token, &cmd[1], len - 2, token_type) == -1)
			return (-1);
		return (len);
	}
	return (-1);
}

static ssize_t	extract_word_token(t_token **lst_token, char *cmd,
		bool *in_double_quote, bool *in_single_quote)
{
	ssize_t	len;

	len = 0;
	if (cmd[0] == '"' || cmd[0] == '\'')
		return (extract_quoted_token(lst_token, cmd, in_double_quote,
				in_single_quote));
	else
	{
		while (cmd[len] && cmd[len] != ' ' && !is_operator(&cmd[len])
			&& cmd[len] != '"' && cmd[len] != '\'')
			len++;
		if (create_token_node(lst_token, cmd, len, T_STRING) == -1)
			return (-1);
		return (len);
	}
}

int	tokenisation(t_token **lst_token, char *cmd)
{
	ssize_t	i;
	ssize_t	token_len;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	in_single_quote = false;
	in_double_quote = false;
	if (!lst_token || !cmd)
		return (-1);
	while (cmd[i])
	{
		while (cmd[i] == ' ' && !in_single_quote && !in_double_quote)
			i++;
		if (!cmd[i])
			break ;
		if (!in_single_quote && !in_double_quote && is_operator(&cmd[i]))
			token_len = get_operator_token(lst_token, &cmd[i]);
		else
			token_len = extract_word_token(lst_token, &cmd[i], &in_double_quote,
					&in_single_quote);
		if (token_len <= 0)
		{
			free_lst_token(lst_token);
			return (-1);
		}
		i += token_len;
	}
	return (0);
}

void	parse(t_token **lst_token, char *cmd)
{
	if (tokenisation(lst_token, cmd) == -1)
		printf("An error occured\n");
	print_lst(*lst_token, "\nToken lst :\n");
}
