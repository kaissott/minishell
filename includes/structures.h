#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_expand_type
{
	T_EXPAND_WORD,
	T_EXPAND_VAR,
}							t_expand_type;

typedef struct s_expand
{
	char					*value;
	t_expand_type			type;
	struct s_expand			*next;
}							t_expand;

typedef enum e_token_chunk_type
{
	T_STRING,
	T_SINGLE_QUOTED,
	T_DOUBLE_QUOTED
}							t_token_chunk_type;

typedef struct s_token_chunk
{
	t_token_chunk_type		type;
	char					*value;
	bool					is_expanded;
	struct s_token_chunk	*next;
}							t_token_chunk;

typedef enum e_token_type
{
	T_ERROR = -1,
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_TRUNC,
	T_REDIR_APPEND,
	T_HEREDOC,
}							t_token_type;

typedef struct s_token
{
	char					*value;
	t_token_chunk			*chunks;
	t_token_type			type;
	bool					is_delimiter;
	struct s_token			*next;
}							t_token;

typedef enum e_parse_error
{
	ERR_NONE = 0,
	ERR_MALLOC = -1,
	ERR_MISSING_SINGLE_QUOTE = -2,
	ERR_MISSING_DOUBLE_QUOTE = -3,
	ERR_SYNTAX = -4,
	ERR_DOUBLE_PIPE = -5,
	ERR_TOKEN = -6,
	ERR_OPEN = -7,
	ERR_CLOSE = -8,
	ERR_PREV_OPEN = -9,
	EMPTY_TOKEN_LIST = -10,
}							t_parse_error;

typedef struct s_error
{
	int						errcode;
	t_parse_error			error_type;
	char					unexpected_token;
}							t_error;

typedef struct s_file
{
	int						fd;
	char					*filepath;
	t_token_type			type;
}							t_file;

typedef struct s_exec
{
	char					**cmd;
	t_file					infile;
	t_file					outfile;
	struct s_exec			*next;
}							t_exec;

typedef struct s_env
{
	char					*env;
	char					*var;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_main
{
	t_env					*env;
	char					**env_tab;
	t_exec					*exec;
	t_token					*token;
	t_error					error;
	int						errcode;
	int						std_in;
	int						std_out;
	char					**envtab;
}							t_main;

t_main						*init_minishell(char **env);

#endif
