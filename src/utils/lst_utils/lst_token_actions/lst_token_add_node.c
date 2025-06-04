#include "../../../../includes/minishell.h"

static t_token	*lst_token_last(t_token *lst_exec)
{
	if (lst_exec)
	{
		while (lst_exec)
		{
			if (lst_exec->next == NULL)
				return (lst_exec);
			lst_exec = lst_exec->next;
		}
	}
	return (NULL);
}

static void	lst_token_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = lst_token_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

t_parse_error	lst_token_add_node(t_token **lst_token, const char *cmd,
		const ssize_t len, t_token_type token_type)
{
	t_token	*token_node;

	token_node = ft_calloc(1, sizeof(t_token));
	if (!token_node)
		return (ERR_MALLOC);
	token_node->type = token_type;
	token_node->value = ft_substr(cmd, 0, len);
	if (!token_node->value)
		return (ERR_MALLOC);
	lst_token_add_back(lst_token, token_node);
	return (ERR_NONE);
}
