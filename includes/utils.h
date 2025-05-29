#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "structures.h"

char	*get_token_error_msg(int err_code);
char	*char_realloc(char *s, char c);
void	free_lst(t_lst_node **lst);
void	free_lst_token(t_token **lst_token);
int		check_file(const char *filepath, t_token_type file_type);

#endif
