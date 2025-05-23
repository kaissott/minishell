#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "structures.h"

char	*get_token_error_msg(int err_code);
char	*char_realloc(char *s, char c);
bool	check_file(char *file);
void	free_lst_token(t_token **lst_token);


#endif
