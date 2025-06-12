#include "../../../../includes/minishell.h"

void	free_exec(t_exec *exec)
{
	size_t	i;

	if (!exec)
		return ;
	if (exec->cmd)
	{
		i = 0;
		while (exec->cmd[i])
		{
			free(exec->cmd[i]);
			i++;
		}
		free(exec->cmd);
	}
	if (exec->heredoc_path)
		free(exec->heredoc_path);
	free(exec);
	exec = NULL;
}

void	free_exec_lst(t_exec **exec_lst)
{
	t_exec	*current;
	t_exec	*next;

	if (!exec_lst || !*exec_lst)
		return ;
	current = *exec_lst;
	while (current)
	{
		next = current->next;
		free_exec(current);
		current = next;
	}
	*exec_lst = NULL;
}
