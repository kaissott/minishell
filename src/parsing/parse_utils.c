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
