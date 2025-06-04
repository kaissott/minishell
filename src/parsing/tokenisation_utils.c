#include "../../includes/minishell.h"

int	is_operator(const char *str)
{
	return (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)
		|| str[0] == '|' || str[0] == '>' || str[0] == '<');
}

static t_token_type	handle_redir(char *cmd, t_error *error)
{
	size_t	i;
	size_t	start;

	i = 1;
	start = 0;
	if ((cmd[0] == '>' && cmd[i] == '>') || (cmd[0] == '<' && cmd[i] == '<'))
		start = 1;
	while (cmd[i] && cmd[i + start] == ' ')
		i++;
	if (is_operator(&cmd[i + start]) || !cmd[i + start])
	{
		set_error(error, ERR_UNEXPECTED_TOKEN, cmd[i + start]);
		return (T_ERROR);
	}
	else if (start == 0)
	{
		if (cmd[0] == '>')
			return (T_REDIR_TRUNC);
		return (T_REDIR_IN);
	}
	else if (cmd[0] == '>')
		return (T_REDIR_APPEND);
	return (T_REDIR_TRUNC);
}

t_token_type	get_token_type(t_error *error, char *cmd)
{
	if (cmd[0] == '|')
	{
		if (cmd[1] == '|')
		{
			set_error(error, ERR_DOUBLE_PIPE, '\0');
			return (T_ERROR);
		}
		return (T_PIPE);
	}
	else if (cmd[0] == '<' || cmd[0] == '>')
		return (handle_redir(cmd, error));
	return (T_STRING);
}

void	toggle_quote_state(char quote_char, bool *in_dquote, bool *in_squote)
{
	if (quote_char == '"' && !*in_squote)
		*in_dquote = !*in_dquote;
	else if (quote_char == '\'' && !*in_dquote)
		*in_squote = !*in_squote;
}

t_token_type	get_token_quoted_type(bool *in_dquote, bool *in_squote)
{
	if (*in_dquote)
		return (T_ENV_STRING);
	else if (*in_squote)
		return (T_STRING);
	return (T_ERROR);
}
