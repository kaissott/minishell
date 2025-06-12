#ifndef LST_UTILS_H
# define LST_UTILS_H

# include "../minishell.h"
# include "../structures.h"

void			exec_lst_add_back(t_exec **exec_lst, t_exec *new);
void			exec_lst_delone(t_exec *lst, t_exec *node_to_delete);
void			print_exec_lst(t_exec *lst, char *msg);
t_parse_error	create_and_add_chunk(t_token_chunk **chunks, char *cmd,
					ssize_t len, char quote);
t_parse_error	token_lst_add_node(t_token **token_lst, char *cmd,
					ssize_t len, t_token_type token_type);
t_parse_error	token_lst_add_chunks(t_env **env_lst, t_token **token_lst,
					t_token *new_token);
void			token_lst_delone(t_token **lst, t_token *node_to_delete);
void			print_token_lst(t_token *lst, char *msg);

#endif
