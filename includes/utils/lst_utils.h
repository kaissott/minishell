#ifndef LST_UTILS_H
# define LST_UTILS_H

# include "../minishell.h"
# include "../structures.h"

t_parse_error	create_and_add_chunk(t_token_chunk **chunk_lst, char *cmd,
					ssize_t len, char quote);
void			chunk_lst_delone(t_token_chunk **chunk_lst,
					t_token_chunk *node_to_delete);
t_parse_error	cat_chunks(t_token *token);

bool			create_env_lst(t_env **env_lst, char **env);
void			free_env_lst(t_env **env_lst);
void			print_env_lst(t_env *lst, char *msg);

t_exec			*create_exec_cmd(void);
void			exec_lst_add_back(t_exec **exec_lst, t_exec *new);
void			exec_lst_delone(t_exec *lst, t_exec *node_to_delete);
void			print_exec_lst(t_exec *lst, char *msg);

void			print_expand_lst(t_expand *lst, char *msg);
t_expand		*create_expand(t_expand_type type, char *value);
void			expand_lst_add_back(t_expand **lst, t_expand *new);

void			print_chunk_lst(t_token_chunk *lst, char *msg);
void			print_token_lst(t_token *lst, char *msg);
t_token			*token_lst_last(t_token *lst);
void			token_lst_delone(t_token **token_lst, t_token *node_to_delete);
void			token_lst_add_back(t_token **token_lst, t_token *new);
t_parse_error	token_lst_add_node(t_token **token_lst, char *cmd, ssize_t len,
					t_token_type token_type);
t_parse_error	token_lst_add_chunks(t_main *shell, t_token *new_token);

void			free_exec(t_exec *exec);
void			free_exec_lst(t_exec **exec_lst);
void			free_token(t_token *token);
void			free_token_lst(t_token **token_lst);

#endif
