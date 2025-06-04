#include "../../../../includes/minishell.h"

t_exec	*lst_create_node(void)
{
	t_exec	*new_node;

	new_node = ft_calloc(1, sizeof(t_exec));
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
