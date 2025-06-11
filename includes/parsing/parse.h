#ifndef PARSE_H
# define PARSE_H

# include "../minishell.h"
# include "../structures.h"

t_parse_error	create_exec_lst(t_exec **exec_lst, t_token **token_lst);
t_exec			*create_exec_cmd(void);
char			**expand_args(char **cmd, char *new_arg);
char			*create_heredoc_filepath(size_t *heredoc_nbr);
int				write_in_heredoc(int *fd_heredoc, const char *next_token_value);

#endif
