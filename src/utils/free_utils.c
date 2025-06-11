#include "../../includes/minishell.h"

void	free_exec_lst(t_exec **exec_lst)
{
	size_t	i;
	t_exec	*current;
	t_exec	*next;

	if (!exec_lst || !*exec_lst)
		return ;
	current = *exec_lst;
	while (current)
	{
		next = current->next;
		if (current->cmd)
		{
			i = 0;
			while (current->cmd[i])
			{
				free(current->cmd[i]);
				i++;
			}
			free(current->cmd);
		}
		free(current);
		current = next;
	}
	*exec_lst = NULL;
}

void	free_token_lst(t_token **token_lst)
{
	t_token			*tmp;
	t_token_chunk	*tmp_word;

	while (*token_lst)
	{
		tmp = (*token_lst)->next;
		if ((*token_lst)->value)
			free((*token_lst)->value);
		else if ((*token_lst)->chunks)
		{
			while ((*token_lst)->chunks)
			{
				tmp_word = (*token_lst)->chunks->next;
				if ((*token_lst)->chunks->value)
					free((*token_lst)->chunks->value);
				free((*token_lst)->chunks);
				(*token_lst)->chunks = tmp_word;
			}
		}
		free(*token_lst);
		*token_lst = tmp;
	}
}

void	free_env_lst(t_env **env_lst)
{
	t_env	*current;
	t_env	*next;

	if (!env_lst || !*env_lst)
		return ;
	current = *env_lst;
	while (current)
	{
		next = current->next;
		if (current->var)
			free(current->var);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*env_lst = NULL;
}

void	free_expand_lst(t_expand **expand_lst)
{
	t_expand	*current;
	t_expand	*next;

	if (!expand_lst || !*expand_lst)
		return ;
	current = *expand_lst;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*expand_lst = NULL;
}

void	clear_and_exit(t_main *main, char *error, int err_number)
{
	// free_struct(main);
	perror(error);
	exit(err_number);
}
