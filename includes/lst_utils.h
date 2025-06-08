#ifndef LST_ACTIONS_H
# define LST_ACTIONS_H

# include "minishell.h"
# include "structures.h"

void			lst_add_back(t_exec **exec_lst, t_exec *new);
t_exec			*lst_create_node(void);
void			lst_delone(t_exec *lst, t_exec *node_to_delete);
void			print_lst(t_exec *lst, char *msg);
t_parse_error	token_lst_add_node(t_token **token_lst, const char *cmd,
					const ssize_t len, t_token_type token_type);
t_parse_error	create_and_add_word_part(t_word_part **parts, const char *cmd,
					const ssize_t len, char quote);
t_parse_error	token_lst_add_token_parts(t_token **token_lst,
					t_token *token_node);
void			token_lst_delone(t_token **lst, t_token *node_to_delete);
void			print_token_lst(t_token *lst, char *msg);

#endif
