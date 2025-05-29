#include "../../../../includes/minishell.h"

t_lst_node	*lst_create_node(void)
{
	t_lst_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_lst_node));
	if (!new_node)
		return (NULL);
	// new_node->value = ft_strdup(value);
	// if (!new_node->value)
	// {
	// 	free(new_node);
	// 	return (NULL);
	// }
	// new_node->type = type;
	return (new_node);
}
