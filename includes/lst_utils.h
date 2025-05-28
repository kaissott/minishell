#ifndef LST_ACTIONS_H
# define LST_ACTIONS_H

# include "minishell.h"
# include "structures.h"

void		lst_add_back(t_lst_node **lst, t_lst_node *new);
void		lst_add_front(t_lst_node **lst, t_lst_node *new);
t_lst_node		*lst_create_node(void);
void		lst_delone(t_lst_node *lst, t_lst_node *node_to_delete);
t_lst_node		*lst_last(t_lst_node *lst);
size_t		lst_size(t_lst_node *lst);
void		print_lst(t_lst_node *lst, char *msg);
void		lst_token_add_back(t_token **lst, t_token *new);
void		lst_token_add_front(t_token **lst, t_token *new);
t_token		*lst_token_create_node(char *value, t_token_type type);
void		lst_token_delone(t_token **lst, t_token *node_to_delete);
t_token		*lst_token_last(t_token *lst);
size_t		lst_token_size(t_token *lst);
void		print_lst_token(t_token *lst, char *msg);

#endif
