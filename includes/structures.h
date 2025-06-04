#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_token_type
{
	T_ERROR = -1,
	T_WORD,
	T_STRING,
	T_ENV_STRING,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_TRUNC,
	T_REDIR_APPEND,
	T_HEREDOC
}						t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef enum e_parse_error
{
	ERR_NONE = 0,
	ERR_MALLOC = -1,
	ERR_MISSING_SINGLE_QUOTE = -2,
	ERR_MISSING_DOUBLE_QUOTE = -3,
	ERR_UNEXPECTED_TOKEN = -4,
	ERR_DOUBLE_PIPE = -5
}							t_parse_error;

typedef struct s_error
{
	t_parse_error	error_type;
	char			unexpected_token;
}					t_error;

typedef struct s_file
{
	int				fd;
	t_token_type	type;
}					t_file;

typedef struct s_lst_node
{
	char				**cmd;
	t_file				infile;
	t_file				outfile;
	struct s_lst_node	*next;
}						t_exec;

typedef struct s_main
{
	char				*env;
	t_exec				*node;
}						t_main;

#endif
