#ifndef PARSE_H
# define PARSE_H

# include "../minishell.h"
# include "../structures.h"

t_parse_error	parsing(t_main *shell);
char			**expand_args(char **cmd, char *new_arg);
t_parse_error	create_heredoc_filepath(t_exec **exec_lst, t_exec *new_node);
int				write_in_heredoc(int *fd_heredoc, const char *next_token_value);

#endif
