#ifndef TOKENISATION_H
# define TOKENISATION_H

# include "minishell.h"
# include "structures.h"

t_parse_error	tokenisation(t_token **token_lst, t_error *error, char *cmd);
int				is_operator(const char *str);
t_token_type	get_token_type(t_error *error, char *cmd);

#endif
