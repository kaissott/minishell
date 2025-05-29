#include "../../includes/minishell.h"

int	is_operator(const char *str)
{
	return (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)
		|| str[0] == '|' || str[0] == '>' || str[0] == '<');
}

static t_token_type	handle_pipe(char *cmd)
{
	if (cmd[1] == '|')
		return (T_DOUBLE_PIPE_ERROR);
	return (T_PIPE);
}

static t_token_type	handle_redir_in(char *cmd)
{
	if (cmd[1] == '<')
	{
		if (is_operator(&cmd[2]))
			return (T_UNEXPECTED_TOKEN);
		return (T_HEREDOC);
	}
	return (T_REDIR_IN);
}

static t_token_type	handle_redir_out(char *cmd)
{
	if (cmd[1] == '>')
	{
		if (is_operator(&cmd[2]))
			return (T_UNEXPECTED_TOKEN);
		return (T_REDIR_APPEND);
	}
	return (T_REDIR_TRUNC);
}

t_token_type	get_token_type(char *cmd)
{
	if (cmd[0] == '|')
		return (handle_pipe(cmd));
	else if (cmd[0] == '<')
		return (handle_redir_in(cmd));
	else if (cmd[0] == '>')
		return (handle_redir_out(cmd));
	return (T_STRING);
}
