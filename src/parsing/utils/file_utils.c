#include "../../../includes/minishell.h"

int	open_file(const char *filepath, t_token_type file_type)
{
	if (file_type == T_REDIR_IN)
		return (open(filepath, O_RDONLY));
	else if (file_type == T_REDIR_TRUNC || file_type == T_HEREDOC)
		return (open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (file_type == T_REDIR_APPEND)
		return (open(filepath, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (-1);
}

t_parse_error	secure_close(int *fd)
{
	if (*fd == -1)
		return (ERR_CLOSE);
	if (*fd > 1)
	{
		if (close(*fd) == -1)
			return (ERR_CLOSE);
		*fd = -1;
	}
	return (ERR_NONE);
}

t_parse_error	check_std_cmd(int std, t_exec *new_cmd)
{
	if (std == STDIN_FILENO)
	{
		if (new_cmd->infile.fd == -1)
			return (ERR_PREV_OPEN);
		if (new_cmd->infile.filepath)
		{
			if (new_cmd->infile.type == T_HEREDOC)
				unlink(new_cmd->infile.filepath);
			free(new_cmd->infile.filepath);
		}
		if (secure_close(&new_cmd->infile.fd) != ERR_NONE)
			return (ERR_CLOSE);
	}
	else if (std == STDOUT_FILENO)
	{
		if (new_cmd->outfile.fd == -1)
			return (ERR_PREV_OPEN);
		if (secure_close(&new_cmd->outfile.fd) != ERR_NONE)
			return (ERR_CLOSE);
	}
	return (ERR_NONE);
}
