#include "../../includes/minishell.h"

t_lst_node	*create_string_node(t_token **token_lst, t_lst_node *new_node,
		size_t word_nbr)
{
	size_t	i;
	size_t	node_value_len;

	i = 0;
	new_node->cmd = ft_calloc(word_nbr + 1, sizeof(char *));
	if (!new_node->cmd)
		return (NULL);
	while (*token_lst && word_nbr > 0)
	{
		node_value_len = ft_strlen((*token_lst)->value);
		new_node->cmd[i] = ft_calloc(node_value_len + 1, sizeof(char));
		if (!new_node->cmd[i])
			return (NULL);
		ft_memcpy(new_node->cmd[i], (*token_lst)->value, node_value_len);
		i++;
		word_nbr--;
		lst_token_delone(token_lst, *token_lst);
	}
	return (new_node);
}

t_lst_node	*handle_redirection(t_token **token_lst, t_token *node,
		t_lst_node *new_node)
{
	if (node->next->value)
	{
		if (node->type == T_REDIR_IN)
		{
			new_node->infile.fd = check_file(node->next->value, node->type);
			new_node->infile.type = node->type;
		}
		else
		{
			new_node->outfile.fd = check_file(node->next->value, node->type);
			new_node->outfile.type = node->type;
		}
	}
	lst_token_delone(token_lst, node->next);
	lst_token_delone(token_lst, node);
	return (new_node);
}

int	create_exec_lst(t_lst_node **lst, t_token **token_lst)
{
	size_t		i;
	t_token		*tmp;
	t_lst_node	*new_node;

	i = 0;
	new_node = ft_calloc(1, sizeof(t_lst_node));
	if (!new_node)
		return (-1);
	while (*token_lst)
	{
		if (!(*token_lst)->next || (*token_lst)->type == T_PIPE)
		{
			printf("in t_pipe or end \n");
			lst_add_back(lst, new_node);
			lst_token_delone(token_lst, *token_lst);
			new_node = ft_calloc(1, sizeof(t_lst_node));
			if (!new_node)
				return (-1);
		}
		if ((*token_lst)->type == T_HEREDOC && (*token_lst)->next)
		{
		}
		if (((*token_lst)->type == T_REDIR_IN
				|| (*token_lst)->type == T_REDIR_TRUNC
				|| (*token_lst)->type == T_REDIR_APPEND) && (*token_lst)->next
			&& (*token_lst)->next->value)
		{
			printf("in t_file \n");
			new_node = handle_redirection(token_lst, *token_lst, new_node);
			if (!new_node)
				return (-1);
			printf("new_node->infile.fd : %d\n", new_node->infile.fd);
			printf("new_node->outfile.fd : %d\n", new_node->outfile.fd);
		}
		else if ((*token_lst)->type == T_WORD
			|| (*token_lst)->type == T_ENV_STRING)
		{
			printf("in t_word \n");
			tmp = *token_lst;
			while (tmp && (tmp->type >= T_WORD && tmp->type <= T_ENV_STRING))
			{
				i++;
				tmp = tmp->next;
			}
			printf("i : %zu\n", i);
			new_node = create_string_node(token_lst, new_node, i);
			if (!new_node)
				return (-1);
			printf("new_node->cmd[0] : %s\n", new_node->cmd[0]);
			i = 0;
		}
	}
	if (new_node && (new_node->cmd || new_node->infile.fd != -1
			|| new_node->outfile.fd != -1))
		lst_add_back(lst, new_node);
	print_lst(*lst, "Exec lst : \n");
	print_lst_token(*token_lst, "Token lst after : \n");
	return (0);
}
