#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_token_type
{
	T_ERROR = -1,
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

typedef enum e_error
{
	WRONG_FILE
}						t_error;

typedef struct s_file
{
	char			*filename;
	t_token_type	type;
}					t_file;

typedef struct s_lst_node
{
	char 				**cmd;
	t_file				infile;
	t_file				outfile;
}						t_lst_node;

typedef struct s_main
{
	char				*env;
	t_lst_node			*node;
}						t_main;

#endif
