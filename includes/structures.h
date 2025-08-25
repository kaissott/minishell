/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 08:06:53 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/23 04:28:38 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

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
	T_ERROR_SYNTAX = -2,
	T_ERROR_PIPE,
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
	bool					is_redir;
	bool					is_blank;
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
	ERR_SIG = -10,
	ERR_AMBIGUOUS_REDIR = -11,
	ERR_PIPE = -12,
	ERR_WRITE_HD = -13,
}							t_parse_error;

typedef struct s_error
{
	char					unexpected_token;
	char					*ambiguous_redir;
	t_parse_error			error_type;
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
	int						fd_heredoc;
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

typedef struct s_shell
{
	t_env					*env;
	char					**env_tab;
	t_exec					*exec;
	t_token					*token;
	t_error					error;
	int						errcode;
	int						std_in;
	int						std_out;
}							t_shell;

t_shell						*init_minishell(char **env);

#endif
