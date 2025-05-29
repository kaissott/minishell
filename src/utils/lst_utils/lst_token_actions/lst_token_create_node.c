#include "../../../../includes/minishell.h"

t_token	*lst_token_create_node(char *value, t_token_type type)
{
	t_token	*new_node;

	new_node = ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = type;
	return (new_node);
}
