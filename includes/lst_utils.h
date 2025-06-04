#ifndef LST_ACTIONS_H
# define LST_ACTIONS_H

# include "minishell.h"
# include "structures.h"

void			lst_add_back(t_exec **lst_exec, t_exec *new);
t_exec			*lst_create_node(void);
void			lst_delone(t_exec *lst, t_exec *node_to_delete);
void			print_lst(t_exec *lst, char *msg);
t_parse_error	lst_token_add_node(t_token **lst_token, const char *cmd,
					const ssize_t len, t_token_type token_type);
void			lst_token_delone(t_token **lst, t_token *node_to_delete);
void			print_lst_token(t_token *lst, char *msg);

#endif
