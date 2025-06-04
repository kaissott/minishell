#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "structures.h"

t_parse_error	tokenisation(t_token **lst_token, t_error *error, char *cmd);
int				is_operator(const char *str);
t_token_type	get_token_type(t_error *error, char *cmd);
void			toggle_quote_state(char quote_char, bool *in_dquote,
					bool *in_squote);
t_token_type	get_token_quoted_type(bool *in_dquote, bool *in_squote);
int				create_exec_lst(t_exec **lst_exec, t_token **token_lst);
void			free_cmd_array(char **cmd);
t_exec			*create_exec_node(void);
size_t			calc_word_nbr(t_token **token_lst);
bool			check_redirection_token(t_token_type token_type);
#endif
