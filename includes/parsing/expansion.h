#ifndef EXPAND_CHUNK_H
# define EXPAND_CHUNK_H

# include "../minishell.h"
# include "../structures.h"

t_parse_error	expansion(t_main *shell);
bool			is_dollar_alone(t_token_chunk *chunk, size_t i, size_t len,
					t_token_chunk *next);
t_expand		*extract_expand_var(char *var, ssize_t *i);
t_parse_error	replace_chunk_value(t_main *shell, t_expand **expand_lst,
					t_token *token, t_token_chunk *chunk);

#endif
