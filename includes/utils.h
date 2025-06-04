#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "structures.h"

void			set_error(t_error *error, t_parse_error error_type,
					char unexpected_token);
void	print_token_error_msg(t_parse_error err_code, char unexpected_token);
char	*char_realloc(char *s, char c);
void	free_lst(t_exec **lst_exec);
void	free_lst_token(t_token **lst_token);
int		check_file(const char *filepath, t_token_type file_type);

#endif
