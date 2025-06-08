#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include "structures.h"

int			create_exec_lst(t_exec **exec_lst, t_token **token_lst);
t_exec		*create_exec_cmd(void);
char		**expand_args(char **cmd, char *new_arg);
int			write_in_heredoc(int *fd_heredoc, const char *next_token_value);
void		print_lst_hd(t_heredoc *lst, char *msg);
t_heredoc	*create_heredoc(t_heredoc **heredoc_lst);

#endif
