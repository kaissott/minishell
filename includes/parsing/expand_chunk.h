#ifndef EXPAND_CHUNK_H
# define EXPAND_CHUNK_H

# include "../minishell.h"
# include "../structures.h"

t_parse_error	expand_chunk(t_env **env_lst, t_token *new_token);
bool			lst_expand_add_back(t_expand **lst,
					t_expand *new);
char			*get_var_value(t_env **env_lst, char *var_name);
t_expand		*create_expand(t_expand_type type, char *value);
void			print_expand_lst(t_expand *lst, char *msg);

#endif
