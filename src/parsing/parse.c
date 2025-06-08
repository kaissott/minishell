#include "../../includes/minishell.h"

static int	handle_redirection(t_exec *new_cmd, t_token **token_lst,
		t_token *token)
{
	if (token->next->value && token->next->type == T_WORD)
	{
		if (token->type == T_REDIR_IN)
		{
			if (new_cmd->infile.fd > 0)
				if (secure_close(&new_cmd->infile.fd) == -1)
					return (-1);
			new_cmd->infile.fd = check_file(token->next->value, token->type);
			new_cmd->infile.type = token->type;
		}
		else
		{
			if (new_cmd->outfile.fd > 0)
				if (secure_close(&new_cmd->outfile.fd) == -1)
					return (-1);
			new_cmd->outfile.fd = check_file(token->next->value, token->type);
			new_cmd->outfile.type = token->type;
		}
		token_lst_delone(token_lst, token->next);
		token_lst_delone(token_lst, token);
		return (0);
	}
	return (-1);
}

static t_exec	*handle_pipe(t_exec **exec_lst, t_exec *new_cmd,
		t_token **token_lst, t_token *token)
{
	lst_add_back(exec_lst, new_cmd);
	token_lst_delone(token_lst, token);
	new_cmd = create_exec_cmd();
	if (!new_cmd)
		return (NULL);
	return (new_cmd);
}

static int	handle_heredoc(t_exec *new_cmd, t_token **token_lst, t_token *token,
		t_heredoc **heredoc_lst)
{
	t_heredoc	*new_heredoc;

	if (!token->next || token->next->type != T_WORD)
		return (-1);
	new_heredoc = create_heredoc(heredoc_lst);
	if (!new_heredoc)
		return (-1);
	new_heredoc->fd = open(new_heredoc->filepath, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (new_heredoc->fd == -1)
		return (-1);
	if (write_in_heredoc(&new_heredoc->fd, token->next->value) == -1)
		return (-1);
	if (secure_close(&new_heredoc->fd) == -1)
		return (-1);
	if (new_cmd->infile.fd > 0)
		close(new_cmd->infile.fd);
	new_cmd->infile.fd = open(new_heredoc->filepath, O_RDONLY);
	new_cmd->infile.type = T_HEREDOC;
	token_lst_delone(token_lst, token->next);
	token_lst_delone(token_lst, token);
	return (0);
}

static int	handle_token(t_exec *new_cmd, t_token **token_lst, t_token *token,
		t_heredoc **heredoc_lst)
{
	if (token->type == T_WORD)
	{
		new_cmd->cmd = expand_args(new_cmd->cmd, token->value);
		if (!new_cmd->cmd)
			return (-1);
		token_lst_delone(token_lst, token);
		return (0);
	}
	else if (token->type == T_HEREDOC)
	{
		if (handle_heredoc(new_cmd, token_lst, token, heredoc_lst) == -1)
			return (-1);
	}
	else if (token->type >= T_REDIR_IN && token->type <= T_REDIR_APPEND)
	{
		if (handle_redirection(new_cmd, token_lst, token) == -1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int	create_exec_lst(t_exec **exec_lst, t_token **token_lst)
{
	t_exec		*new_cmd;
	t_heredoc	*heredoc_lst;

	heredoc_lst = NULL;
	new_cmd = create_exec_cmd();
	if (!new_cmd)
		return (-1);
	while (*token_lst)
	{
		if ((*token_lst)->type == T_PIPE)
		{
			new_cmd = handle_pipe(exec_lst, new_cmd, token_lst, *token_lst);
			if (!new_cmd)
				return (-1);
		}
		if (handle_token(new_cmd, token_lst, *token_lst, &heredoc_lst) == -1)
			return (-1);
	}
	if (new_cmd)
		lst_add_back(exec_lst, new_cmd);
	print_lst_hd(heredoc_lst, "LST HEREDOC AT END : \n");
	free_heredoc_lst(&heredoc_lst);
	return (0);
}
