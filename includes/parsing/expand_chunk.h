#ifndef EXPAND_CHUNK_H
# define EXPAND_CHUNK_H

# include "../minishell.h"
# include "../structures.h"

t_parse_error	expand_chunk(t_env **env_lst, t_token *new_token);
char			*get_var_value(t_env **env_lst, char *var_name);

#endif
