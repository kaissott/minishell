#include "../../includes/minishell.h"

t_lst_node	*create_cmd_lst_node(char *filename, t_token_type file_type)
{
	int			fd;
	t_lst_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_lst_node));
	if (!new_node)
		return (NULL);
	if (filename)
	{
		fd = check_file(filename, file_type);
		printf("fd : %d\n", fd);
		if (fd == -1)
			return (NULL);
		if (file_type == T_REDIR_IN)
		{
			new_node->infile.fd = fd;
			new_node->infile.type = file_type;
		}
		else
		{
			new_node->outfile.fd = fd;
			new_node->outfile.type = file_type;
		}
	}
	return (new_node);
}

int	create_string_node(t_lst_node **lst, t_token **token_lst, size_t word_nbr)
{
	size_t		i;
	size_t		node_value_len;
	t_lst_node	*new_node;

	i = 0;
	new_node = ft_calloc(1, sizeof(t_lst_node));
	if (!new_node)
		return (-1);
	new_node->cmd = ft_calloc(word_nbr + 1, sizeof(char *));
	if (!new_node->cmd)
		return (-1);
	while ((*token_lst) && word_nbr > 0)
	{
		printf("cmd[i] : %s\n", (*token_lst)->value);
		node_value_len = ft_strlen((*token_lst)->value);
		new_node->cmd[i] = ft_calloc(node_value_len + 1, sizeof(char));
		if (!new_node->cmd[i])
			return (-1);
		ft_memcpy(new_node->cmd[i], (*token_lst)->value, node_value_len);
		printf("new_node cmd : %s\n", new_node->cmd[i]);
		i++;
		word_nbr--;
		lst_token_delone(token_lst, *token_lst);
	}
	lst_add_back(lst, new_node);
	return (0);
}

int	handle_redirection(t_lst_node **lst, t_token **token_lst, t_token *node)
{
	t_lst_node	*new_node;

	// printf("function node->type == 4 || 5 || 6\n");
	// printf("node->value %s\n", node->value);
	new_node = create_cmd_lst_node(node->next->value, node->type);
	if (!new_node)
		return (-1);
	lst_add_back(lst, new_node);
	lst_token_delone(token_lst, node->next);
	lst_token_delone(token_lst, node);
	return (0);
}

int	create_exec_lst(t_lst_node **lst, t_token **token_lst)
{
	size_t	i;
	t_token	*tmp;

	i = 0;
	while ((*token_lst))
	{
		if (((*token_lst)->type == T_REDIR_IN
				|| (*token_lst)->type == T_REDIR_TRUNC
				|| (*token_lst)->type == T_REDIR_APPEND) && (*token_lst)->next
			&& (*token_lst)->next->value)
		{
			if (handle_redirection(lst, token_lst, *token_lst) == -1)
				return (-1);
		}
		else if ((*token_lst)->type == T_WORD
			|| (*token_lst)->type == T_ENV_STRING)
		{
			tmp = *token_lst;
			while (tmp && (tmp->type >= T_WORD && tmp->type <= T_ENV_STRING))
			{
				i++;
				tmp = tmp->next;
			}
			printf("i : %zu\n", i);
			if (create_string_node(lst, token_lst, i) == -1)
				return (-1);
			i = 0;
		}
		else
			lst_token_delone(token_lst, *token_lst);
	}
	print_lst(*lst, "Exec lst : \n");
	print_lst_token(*token_lst, "Token lst after : \n");
	return (0);
}
