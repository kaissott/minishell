#include "../../includes/minishell.h"

static t_exec	*handle_pipe(t_exec **exec_lst, t_exec *new_cmd,
		t_token **token_lst, t_token *token)
{
	exec_lst_add_back(exec_lst, new_cmd);
	token_lst_delone(token_lst, token);
	return (create_exec_cmd());
}

static t_parse_error	handle_redirection(t_exec *new_cmd, t_token **token_lst,
		t_token *token)
{
	int	std;

	std = 1;
	if (token->type == T_REDIR_IN)
	{
		std = 0;
		new_cmd->infile.type = token->type;
	}
	else
		new_cmd->outfile.type = token->type;
	if (!token->next || token->next->type != T_WORD)
		return (ERR_UNFINISHED_REDIR);
	if (check_std_cmd(std, new_cmd) != ERR_NONE)
		return (ERR_CLOSE);
	if (std == 0)
		new_cmd->infile.fd = open_file(token->next->value, token->type);
	else
	{
		new_cmd->outfile.fd = open_file(token->next->value, token->type);
		if (new_cmd->outfile.fd == -1)
			return (ERR_OPEN);
	}
	token_lst_delone(token_lst, token->next);
	token_lst_delone(token_lst, token);
	return (ERR_NONE);
}

static t_parse_error	handle_heredoc(t_exec **exec_lst, t_exec *new_cmd,
		t_token **token_lst, t_token *token)
{
	new_cmd->infile.type = T_HEREDOC;
	if (!token->next || token->next->type != T_WORD)
		return (ERR_UNFINISHED_REDIR);
	if (check_std_cmd(0, new_cmd) != ERR_NONE)
		return (ERR_CLOSE);
	if (create_heredoc_filepath(exec_lst, new_cmd) != ERR_NONE)
		return (ERR_MALLOC);
	new_cmd->infile.fd = open_file(new_cmd->heredoc_path, token->type);
	if (new_cmd->infile.fd == -1)
		return (ERR_OPEN);
	if (write_in_heredoc(&new_cmd->infile.fd, token->next->value) != ERR_NONE)
		return (ERR_CLOSE);
	new_cmd->infile.fd = open(new_cmd->heredoc_path, O_RDONLY);
	if (new_cmd->infile.fd == -1)
		return (ERR_OPEN);
	token_lst_delone(token_lst, token->next);
	token_lst_delone(token_lst, token);
	return (ERR_NONE);
}

static t_parse_error	handle_token(t_exec **exec_lst, t_exec *new_cmd,
		t_token **token_lst, t_token *token)
{
	if (token->type == T_WORD)
	{
		new_cmd->cmd = expand_args(new_cmd->cmd, token->value);
		if (!new_cmd->cmd)
			return (ERR_MALLOC);
		token_lst_delone(token_lst, token);
		return (ERR_NONE);
	}
	else if (token->type >= T_REDIR_IN && token->type <= T_HEREDOC)
	{
		if (token->type == T_HEREDOC)
			return (handle_heredoc(exec_lst, new_cmd, token_lst, token));
		else
			return (handle_redirection(new_cmd, token_lst, token));
	}
	return (ERR_TOKEN);
}

t_parse_error	parsing(t_exec **exec_lst, t_token **token_lst)
{
	t_exec			*new_cmd;
	t_parse_error	ret;

	new_cmd = create_exec_cmd();
	if (!new_cmd)
		return (ERR_MALLOC);
	while (*token_lst)
	{
		if ((*token_lst)->type == T_PIPE)
		{
			new_cmd = handle_pipe(exec_lst, new_cmd, token_lst, *token_lst);
			if (!new_cmd)
				return (ERR_MALLOC);
		}
		else
		{
			ret = handle_token(exec_lst, new_cmd, token_lst, *token_lst);
			if (ret != ERR_NONE)
			{
				free_exec(new_cmd);
				return (ret);
			}
		}
	}
	if (new_cmd)
		exec_lst_add_back(exec_lst, new_cmd);
	return (ERR_NONE);
}
