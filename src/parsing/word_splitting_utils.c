#include "../../includes/minishell.h"

bool	contains_ifs_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}

void	replace_split_token(t_token **tokens, t_token *new_tokens,
		t_token *token)
{
	t_token	*tmp;
	t_token	*prev;
	t_token	*last;

	tmp = *tokens;
	prev = NULL;
	while (tmp && tmp != token)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	last = new_tokens;
	while (last->next)
		last = last->next;
	last->next = tmp->next;
	if (!prev)
		*tokens = new_tokens;
	else
		prev->next = new_tokens;
	free_token(tmp);
	tmp = NULL;
}
