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

char	*create_heredoc_filepath(size_t *heredoc_nbr)
{
	char	*filepath;
	char	*heredoc_nbr_str;

	heredoc_nbr_str = ft_itoa(*heredoc_nbr);
	if (!heredoc_nbr_str)
		return (NULL);
	filepath = ft_strjoin("tmp/.ms_hd_", heredoc_nbr_str);
	free(heredoc_nbr_str);
	if (!filepath)
		return (NULL);
	*heredoc_nbr += 1;
	return (filepath);
}

int	write_in_heredoc(int *fd_heredoc, const char *next_token_value)
{
	char	*rl;

	while (1)
	{
		rl = readline("heredoc>");
		if (!rl)
		{
			if (secure_close(fd_heredoc) == -1)
				return (-1);
			return (0);
		}
		if (ft_strcmp(rl, next_token_value) == 0)
		{
			free(rl);
			break ;
		}
		ft_putendl_fd(rl, *fd_heredoc);
		free(rl);
	}
	return (0);
}
