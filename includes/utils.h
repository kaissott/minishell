#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "structures.h"

void	set_error(t_error *error, t_parse_error error_type,
			char unexpected_token);
void	print_token_error_msg(t_parse_error err_code, char unexpected_token);
char	*char_realloc(char *s, char c);
int		secure_open(int *fd, const char *filepath);
int		secure_close(int *fd);
int		check_file(const char *filepath, t_token_type file_type);
void	free_exec_lst(t_exec **exec_lst);
void	free_token_lst(t_token **token_lst);
void	free_heredoc_lst(t_heredoc **heredoc_lst);


#endif
