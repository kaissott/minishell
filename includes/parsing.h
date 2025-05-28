#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "structures.h"

void			parse(t_lst_node **lst, t_token **lst_token, char *cmd);
int				is_operator(const char *str);
t_token_type	get_token_type(char *cmd);
ssize_t			create_token_node(t_token **lst_token, const char *cmd,
					const ssize_t len, t_token_type type);
ssize_t			get_operator_token(t_token **lst_token, char *cmd);
void			toggle_quote_state(char quote_char, bool *in_double_quote,
					bool *in_single_quote);
int				create_exec_lst(t_lst_node **lst, t_token **token_lst);

#endif
