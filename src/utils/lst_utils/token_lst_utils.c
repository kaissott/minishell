#include "../../../includes/minishell.h"

t_token	*token_lst_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	token_lst_delone(t_token **token_lst, t_token *node_to_delete)
{
	t_token	*tmp;

	if (!token_lst || !*token_lst || !node_to_delete)
		return ;
	if (*token_lst == node_to_delete)
	{
		*token_lst = node_to_delete->next;
		free_token(node_to_delete);
		return ;
	}
	tmp = *token_lst;
	while (tmp && tmp->next != node_to_delete)
		tmp = tmp->next;
	if (tmp && tmp->next == node_to_delete)
	{
		tmp->next = node_to_delete->next;
		free_token(node_to_delete);
	}
}

void	token_lst_add_back(t_token **token_lst, t_token *new)
{
	t_token	*tmp;

	if (!token_lst || !new)
		return ;
	if (!*token_lst)
	{
		*token_lst = new;
		return ;
	}
	tmp = *token_lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

t_parse_error	token_lst_add_node(t_token **token_lst, char *cmd, ssize_t len,
		t_token_type token_type)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (ERR_MALLOC);
	new_token->type = token_type;
	new_token->value = ft_substr(cmd, 0, len);
	if (!new_token->value)
	{
		free(new_token);
		return (ERR_MALLOC);
	}
	token_lst_add_back(token_lst, new_token);
	return (ERR_NONE);
}

t_parse_error	token_lst_add_chunks(t_main *shell, t_token *new_token)
{
	t_token_chunk	*tmp;
	char			*prev;

	tmp = new_token->chunks;
	new_token->type = T_WORD;
	while (tmp)
	{
		prev = new_token->value;
		new_token->value = join_or_dup(prev, tmp->value);
		if (!new_token->value)
		{
			free_token(new_token);
			return (ERR_MALLOC);
		}
		tmp = tmp->next;
	}
	token_lst_add_back(&shell->token, new_token);
	return (ERR_NONE);
}

void	print_token_lst(t_token *lst, char *msg)
{
	size_t			i;
	t_token_chunk	*tmp;

	i = 1;
	printf("\n%s\n", msg);
	if (!lst)
	{
		printf("The token list is empty\n");
		return ;
	}
	while (lst)
	{
		printf("Token node [%zu]\n", i++);
		if (lst->value)
			printf("\tvalue: [%s] ", lst->value);
		else
			printf("\tvalue: [NULL] ");
		printf("type: [%d] is_delimiter : [%d]\n", lst->type,
			lst->is_delimiter);
		if (lst->chunks)
		{
			tmp = lst->chunks;
			while (tmp)
			{
				printf("\tchunk value: [%s] type : [%d] is_expanded : [%d]\n",
					tmp->value, tmp->type, tmp->is_expanded);
				tmp = tmp->next;
			}
		}
		lst = lst->next;
	}
}
