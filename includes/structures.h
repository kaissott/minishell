/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:04:19 by luca              #+#    #+#             */
/*   Updated: 2025/05/20 18:43:50 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
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

typedef enum e_type
{
	T_FILE,
	T_COMMAND,
}						t_type;

typedef struct s_cmd_node
{
	char				*cmd;
	char				**arg;
}						t_cmd_node;

typedef struct s_file
{
	char				*filename;
	bool				std;
	struct s_file		*next;
}						t_file;

typedef struct s_lst_node
{
	t_cmd_node			cmd_node;
	struct s_file		*infile;
	struct s_file		*outfile;
	bool				outfile_type;
	struct s_lst_node	*next;
}						t_lst_node;

typedef struct s_main
{
	char				*env;
	t_lst_node			*node;
}						t_main;

#endif
