#ifndef EXPAND_CHUNK_H
# define EXPAND_CHUNK_H

# include "../minishell.h"
# include "../structures.h"

t_parse_error	expansion(t_main *shell);
void			remove_char_at(char *str, size_t i);
bool			contains_ifs_chars(char *str);
t_parse_error	replace_chunk_value(t_main *shell, t_expand **expand_lst,
					t_token *token,t_token_chunk *chunk);
void			free_expand_lst(t_expand **expand_lst);

#endif
