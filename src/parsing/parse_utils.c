#include "../../includes/minishell.h"

t_exec	*create_exec_cmd(void)
{
	t_exec	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_exec));
	if (!new_cmd)
		return (NULL);
	new_cmd->infile.fd = -1;
	new_cmd->outfile.fd = -1;
	return (new_cmd);
}

char	**expand_args(char **cmd, char *new_arg)
{
	size_t	i;
	size_t	len;
	char	**new_cmd;

	i = 0;
	len = 0;
	while (cmd && cmd[len])
		len++;
	new_cmd = ft_calloc(len + 2, sizeof(char *));
	if (!new_cmd)
		return (NULL);
	while (i < len)
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	new_cmd[len] = ft_strdup(new_arg);
	if (!new_cmd[len])
		return (NULL);
	free(cmd);
	return (new_cmd);
}

t_parse_error	create_heredoc_filepath(t_exec **exec_lst, t_exec *new_node)
{
	int		i;
	char	*cmd_nbr;
	t_exec	*tmp;

	i = 0;
	tmp = *exec_lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	cmd_nbr = ft_itoa(i);
	if (!cmd_nbr)
		return (ERR_MALLOC);
	new_node->heredoc_path = ft_strjoin("tmp/.ms_hd_", cmd_nbr);
	free(cmd_nbr);
	if (!new_node->heredoc_path)
		return (ERR_MALLOC);
	return (ERR_NONE);
}

t_parse_error	write_in_heredoc(int *fd_heredoc, const char *next_token_value)
{
	char	*rl;

	while (1)
	{
		rl = readline("heredoc>");
		if (!rl)
			return (ERR_NONE);
		if (ft_strcmp(rl, next_token_value) == 0)
		{
			free(rl);
			break ;
		}
		ft_putendl_fd(rl, *fd_heredoc);
		free(rl);
	}
	if (secure_close(fd_heredoc) != ERR_NONE)
		return (ERR_CLOSE);
	return (ERR_NONE);
}
