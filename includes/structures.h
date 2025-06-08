#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_token_type
{
	T_ERROR = -1,
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_TRUNC,
	T_REDIR_APPEND,
	T_HEREDOC,
}	t_token_type;

typedef enum e_word_part_type
{
	T_ERROR_WORD = -1,
	T_STRING,
	T_ENV_STRING,
	T_EOF
}	t_word_part_type;

typedef struct s_word_part
{
	t_word_part_type	type;
	char				*value;
	struct s_word_part	*next;
}	t_word_part;

typedef struct s_token
{
	char			*value;
	t_word_part		*parts;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_parse_error
{
	ERR_NONE = 0,
	ERR_MALLOC = -1,
	ERR_MISSING_SINGLE_QUOTE = -2,
	ERR_MISSING_DOUBLE_QUOTE = -3,
	ERR_UNEXPECTED_TOKEN = -4,
	ERR_DOUBLE_PIPE = -5
}	t_parse_error;

typedef struct s_error
{
	t_parse_error	error_type;
	char			unexpected_token;
}	t_error;

typedef struct s_here_doc
{
	int					fd;
	char				*filepath;
	struct s_here_doc	*next;
}	t_heredoc;

typedef struct s_file
{
	int				fd;
	t_token_type	type;
}	t_file;

typedef struct s_exec
{
	char			**cmd;
	t_file			infile;
	t_file			outfile;
	struct s_exec	*next;
}	t_exec;

typedef struct s_main
{
	char	*env;
	t_exec	*node;
}	t_main;

#endif
