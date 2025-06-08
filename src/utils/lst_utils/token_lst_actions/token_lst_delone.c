#include "../../../../includes/minishell.h"

static void	free_token(t_token *node)
{
	t_word_part	*next;

	if (!node)
		return ;
	if (node->value)
		free(node->value);
	while (node->parts)
	{
		next = node->parts->next;
		if (node->parts->value)
			free(node->parts->value);
		free(node->parts);
		node->parts = next;
	}
	free(node);
}

void	token_lst_delone(t_token **lst, t_token *node_to_delete)
{
	t_token	*tmp;

	if (!lst || !*lst || !node_to_delete)
		return ;
	if (*lst == node_to_delete)
	{
		*lst = node_to_delete->next;
		free_token(node_to_delete);
		return ;
	}
	tmp = *lst;
	while (tmp)
	{
		if (tmp->next == node_to_delete)
		{
			tmp->next = node_to_delete->next;
			free_token(node_to_delete);
			return ;
		}
		tmp = tmp->next;
	}
}
