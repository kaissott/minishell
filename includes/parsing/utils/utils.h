#ifndef UTILS_H
# define UTILS_H

# include "../../minishell.h"
# include "../../structures.h"

int				open_file(const char *filepath, t_token_type file_type);
t_parse_error	secure_close(int *fd);
t_parse_error	check_std_cmd(int std, t_exec *new_cmd);

void			free_shell(t_main *shell, t_parse_error errcode);
void			clear_and_exit(t_main *shell, t_parse_error errcode);

bool			check_parsing(t_main *shell, t_parse_error errcode,
					bool at_end);
void			get_errcode(t_main *shell, t_parse_error errcode);

t_parse_error	set_error(t_error *error, t_parse_error error_type,
					char unexpected_token);
void			print_syntax_error_msg(t_parse_error errcode,
					char unexpected_token);
char			*join_or_dup(char *prev, char *next);

#endif
