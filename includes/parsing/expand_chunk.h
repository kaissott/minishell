#ifndef EXPAND_CHUNK_H
# define EXPAND_CHUNK_H

# include "../minishell.h"
# include "../structures.h"

t_parse_error	expand_chunk(t_main *shell, t_token *new_token);
t_parse_error	replace_chunk_value(t_main *shell, t_expand **expand_lst,
					t_token_chunk *chunk);
void			free_expand_lst(t_expand **expand_lst);

#endif
