#include "../../../includes/minishell.h"

static void	chunk_lst_add_back(t_token_chunk **chunk_lst, t_token_chunk *new)
{
	t_token_chunk	*tmp;

	if (!chunk_lst || !new)
		return ;
	if (!*chunk_lst)
		*chunk_lst = new;
	else
	{
		tmp = *chunk_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_parse_error	create_and_add_chunk(t_token_chunk **chunk_lst, char *cmd,
		ssize_t len, char quote)
{
	t_token_chunk	*new_chunk;

	new_chunk = ft_calloc(1, sizeof(t_token_chunk));
	if (!new_chunk)
		return (ERR_MALLOC);
	if (quote == '\'')
		new_chunk->type = T_STRING;
	else
		new_chunk->type = T_ENV_STRING;
	new_chunk->value = ft_substr(cmd, 0, len);
	if (!new_chunk->value)
	{
		free(new_chunk);
		return (ERR_MALLOC);
	}
	chunk_lst_add_back(chunk_lst, new_chunk);
	return (ERR_NONE);
}

// void	add_expand_token(t_token **tokens, char *chunk)
// {
// 	size_t	i;
// 	char	**splited_chunk;
// 	t_token	*new_token;

// 	i = 0;
// 	splited_chunk = ft_split(chunk, ' ');
// 	if (!splited_chunk)
// 		return (NULL);
// 	while (splited_chunk[i])
// 	{
// 		new_token = ft_calloc(1, sizeof(t_token));
// 		if (!new_token)
// 			return (NULL);
// 		new_token->value = splited_chunk[i];
// 		token_lst_add_back(tokens, new_token);
// 		i++;
// 	}
// 	print_token_lst(tokens, "TOKENS LST AFETER EXPAND : \n");
// 	free(splited_chunk);
// }

// t_token	*split_expanded_token(t_token *token)
// {
// 	t_token			*tokens;
// 	t_token_chunk	*tmp;

// 	token = NULL;
// 	tmp = token->chunks;
// 	while (tmp)
// 	{
// 		if (ft_strchr(tmp->value, ' '))
// 			add_expand_token(tokens, tmp->value);
// 		tmp = tmp->next;
// 	}
// }
