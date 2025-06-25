#include "../../includes/minishell.h"

static t_exec	*handle_pipe(t_main *shell, t_token *token, t_exec *new_cmd)
{
	exec_lst_add_back(&shell->exec, new_cmd);
	token_lst_delone(&shell->token, token);
	return (create_exec_cmd());
}

static t_parse_error	handle_redirection(t_main *shell, t_token *token,
		t_exec *new_cmd)
{
	int	std;

	std = STDOUT_FILENO;
	if (token->type == T_REDIR_IN)
	{
		std = STDIN_FILENO;
		new_cmd->infile.type = token->type;
	}
	else
		new_cmd->outfile.type = token->type;
	if (check_std_cmd(std, new_cmd) != ERR_NONE)
		return (ERR_CLOSE);
	if (std == STDIN_FILENO)
	{
		new_cmd->infile.filepath = ft_strdup(token->next->value);
		if (!new_cmd->infile.filepath)
			return (ERR_MALLOC);
		new_cmd->infile.fd = open_file(token->next->value, token->type);
		if (new_cmd->infile.fd == -1)
			perror(new_cmd->infile.filepath);
	}
	else
	{
		new_cmd->outfile.filepath = ft_strdup(token->next->value);
		if (!new_cmd->outfile.filepath)
			return (ERR_MALLOC);
		new_cmd->outfile.fd = open_file(token->next->value, token->type);
		if (new_cmd->outfile.fd == -1)
			perror(new_cmd->outfile.filepath);
	}
	token_lst_delone(&shell->token, token->next);
	token_lst_delone(&shell->token, token);
	return (ERR_NONE);
}

static t_parse_error	handle_heredoc(t_main *shell, t_token *token,
		t_exec *new_cmd)
{
	new_cmd->infile.type = T_HEREDOC;
	if (check_std_cmd(0, new_cmd) != ERR_NONE)
		return (ERR_CLOSE);
	if (create_heredoc_filepath(&shell->exec, new_cmd) != ERR_NONE)
		return (ERR_MALLOC);
	new_cmd->infile.fd = open_file(new_cmd->infile.filepath, token->type);
	// if (new_cmd->infile.fd == -1)
	// 	return (ERR_OPEN);
	if (write_in_heredoc(&new_cmd->infile.fd, token->next->value) != ERR_NONE)
		return (ERR_CLOSE);
	new_cmd->infile.fd = open(new_cmd->infile.filepath, O_RDONLY);
	// if (new_cmd->infile.fd == -1)
	// 	return (ERR_OPEN);
	token_lst_delone(&shell->token, token->next);
	token_lst_delone(&shell->token, token);
	return (ERR_NONE);
}

static t_parse_error	handle_token(t_main *shell, t_token *token,
		t_exec *new_cmd)
{
	if (token->type == T_WORD)
	{
		new_cmd->cmd = expand_args(new_cmd->cmd, token->value);
		if (!new_cmd->cmd)
			return (ERR_MALLOC);
		token_lst_delone(&shell->token, token);
		return (ERR_NONE);
	}
	else if (token->type >= T_REDIR_IN && token->type <= T_HEREDOC)
	{
		if (token->type == T_HEREDOC)
			return (handle_heredoc(shell, token, new_cmd));
		else
			return (handle_redirection(shell, token, new_cmd));
	}
	return (ERR_TOKEN);
}

t_parse_error	parsing(t_main *shell)
{
	t_exec			*new_cmd;
	t_parse_error	ret;

	new_cmd = create_exec_cmd();
	if (!new_cmd)
		return (ERR_MALLOC);
	while (shell->token)
	{
		if (shell->token->type == T_PIPE)
		{
			new_cmd = handle_pipe(shell, shell->token, new_cmd);
			if (!new_cmd)
				return (ERR_MALLOC);
		}
		else
		{
			ret = handle_token(shell, shell->token, new_cmd);
			if (ret != ERR_NONE)
			{
				free_exec(new_cmd);
				return (ret);
			}
		}
	}
	if (new_cmd)
		exec_lst_add_back(&shell->exec, new_cmd);
	// print_exec_lst(*exec_lst, "EXEC LST BEFORE EXEC :\n");
	return (ERR_NONE);
}
