#include "../../includes/minishell.h"

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

static t_parse_error	handle_redirection(t_exec *new_cmd, t_token **token_lst,
		t_token *token)
{
	if (!token->next->value || token->next->type != T_WORD)
		return (ERR_UNFINISHED_REDIR);
	if (token->type == T_REDIR_IN)
	{
		if (new_cmd->infile.fd > 0)
			if (secure_close(&new_cmd->infile.fd) == -1)
				return (ERR_CLOSE);
		new_cmd->infile.fd = check_file(token->next->value, token->type);
		new_cmd->infile.type = token->type;
	}
	else
	{
		if (new_cmd->outfile.fd > 0)
			if (secure_close(&new_cmd->outfile.fd) == -1)
				return (ERR_CLOSE);
		new_cmd->outfile.fd = check_file(token->next->value, token->type);
		new_cmd->outfile.type = token->type;
	}
	token_lst_delone(token_lst, token->next);
	token_lst_delone(token_lst, token);
	return (ERR_NONE);
}

static t_parse_error	handle_heredoc(t_exec *new_cmd, t_token **token_lst,
		t_token *token, size_t *heredoc_nbr)
{
	int		fd;
	char	*filepath;

	if (!token->next || token->next->type != T_WORD)
		return (ERR_UNFINISHED_REDIR);
	filepath = create_heredoc_filepath(heredoc_nbr);
	if (!filepath)
	{
		printf("No filepath error\n");
		return (ERR_MALLOC);
	}
	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || write_in_heredoc(&fd, token->next->value) == -1
		|| secure_close(&fd) == -1)
	{
		printf("fd |l write in hd || secure clode error\n");
		free(filepath);
		return (ERR_MALLOC);
	}
	if (new_cmd->infile.fd > 0)
		close(new_cmd->infile.fd);
	new_cmd->infile.fd = secure_open(&fd, filepath);
	if (new_cmd->infile.fd == -1)
	{
		printf("newcmd fd error\n");
		unlink(filepath);
		free(filepath);
		return (ERR_MALLOC);
	}
	unlink(filepath); // Fichier supprimé une fois ouvert en lecture
	new_cmd->infile.type = T_HEREDOC;
	token_lst_delone(token_lst, token->next);
	token_lst_delone(token_lst, token);
	free(filepath);
	return (ERR_NONE);
}

static t_parse_error	handle_token(t_exec *new_cmd, t_token **token_lst,
		t_token *token, size_t *heredoc_nbr)
{
	if (token->type == T_WORD)
	{
		new_cmd->cmd = expand_args(new_cmd->cmd, token->value);
		if (!new_cmd->cmd)
		{
			printf("ret handle token expand args error \n");
			return (ERR_MALLOC);
		}
		token_lst_delone(token_lst, token);
		return (ERR_NONE);
	}
	else if (token->type == T_HEREDOC)
	{
		printf("ret heredoc \n");
		return (handle_heredoc(new_cmd, token_lst, token, heredoc_nbr));
	}
	else if (token->type >= T_REDIR_IN && token->type <= T_REDIR_APPEND)
	{
		printf("ret redir \n");
		return (handle_redirection(new_cmd, token_lst, token));
	}
	return (ERR_NONE);
}

t_parse_error	create_exec_lst(t_exec **exec_lst, t_token **token_lst)
{
	size_t			heredoc_nbr;
	t_exec			*new_cmd;
	t_parse_error	ret;

	heredoc_nbr = 0;
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
			ret = handle_token(new_cmd, token_lst, *token_lst, &heredoc_nbr);
			if (ret != ERR_NONE)
				return (ret);
		}
	}
	if (new_cmd)
		lst_add_back(exec_lst, new_cmd);
	printf("final finish exec\n");
	return (ERR_NONE);
}
