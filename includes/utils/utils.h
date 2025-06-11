#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"
# include "../structures.h"

bool	create_env_lst(t_env **env_lst, char **env);
void	print_env_lst(t_env *lst, char *msg);
ssize_t	set_error(t_error *error, t_parse_error error_type,
			char unexpected_token);
void	print_token_error_msg(t_parse_error err_code, char unexpected_token);
char	*join_or_dup(char *prev, char *next);
int		secure_open(int *fd, const char *filepath);
int		secure_close(int *fd);
int		check_file(const char *filepath, t_token_type file_type);
void	free_exec_lst(t_exec **exec_lst);
void	free_token_lst(t_token **token_lst);
void	free_expand_lst(t_expand **expand_lst);

#endif
