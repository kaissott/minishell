#ifndef LST_ACTIONS_H
# define LST_ACTIONS_H

# include "minishell.h"
# include "structures.h"

void		lst_add_back(t_token **lst, t_token *new);
void		lst_add_front(t_token **lst, t_token *new);
t_token	*lst_create_node(char *value, t_token_type type);
void		lst_delone(t_token *lst, t_token *node_to_delete);
t_token	*lst_last(t_token *lst);
size_t		lst_size(t_token *lst);
void	print_lst(t_token *lst, char *msg);

#endif
