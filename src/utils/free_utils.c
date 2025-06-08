#include "../../includes/minishell.h"

void	free_exec_lst(t_exec **exec_lst)
{
	t_exec	*tmp;
	size_t	i;

	while (*exec_lst)
	{
		i = 0;
		tmp = (*exec_lst)->next;
		if ((*exec_lst)->cmd)
		{
			while ((*exec_lst)->cmd[i])
			{
				free((*exec_lst)->cmd[i]);
				i++;
			}
			free((*exec_lst)->cmd);
		}
		free(*exec_lst);
		*exec_lst = tmp;
	}
}

void	free_token_lst(t_token **token_lst)
{
	t_token		*tmp;
	t_word_part	*tmp_word;

	while (*token_lst)
	{
		tmp = (*token_lst)->next;
		if ((*token_lst)->value)
			free((*token_lst)->value);
		else if ((*token_lst)->parts)
		{
			while ((*token_lst)->parts)
			{
				tmp_word = (*token_lst)->parts->next;
				if ((*token_lst)->parts->value)
					free((*token_lst)->parts->value);
				free((*token_lst)->parts);
				(*token_lst)->parts = tmp_word;
			}
		}
		free(*token_lst);
		*token_lst = tmp;
	}
}

void	free_heredoc_lst(t_heredoc **heredoc_lst)
{
	t_heredoc	*tmp;

	while (*heredoc_lst)
	{
		tmp = (*heredoc_lst)->next;
		if ((*heredoc_lst)->filepath)
		{
			unlink((*heredoc_lst)->filepath);
			free((*heredoc_lst)->filepath);
		}
		if ((*heredoc_lst)->fd > 0)
			secure_close(&(*heredoc_lst)->fd);
		free(*heredoc_lst);
		*heredoc_lst = tmp;
	}
}
