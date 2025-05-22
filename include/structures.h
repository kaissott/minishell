/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:04:19 by luca              #+#    #+#             */
/*   Updated: 2025/05/21 02:57:59 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_TRUNC,
	T_REDIR_APPEND,
	T_HEREDOC
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef enum e_error
{
	WRONG_FILE
}					t_error;

typedef enum e_type
{
	T_FILE,
	T_COMMAND,
}					t_type;

typedef struct s_file
{
	char			*filename;
	t_token_type	type;
}					t_file;

typedef struct s_lst_node
{
	char			*cmd;
	struct s_file	infile;
	struct s_file	outfile;
}					t_lst_node;

typedef struct s_env
{
	char			*env;
	struct t_env	*next;
}					t_env;

typedef struct s_main
{
	char			*mainenv;
	t_lst_node		*node;
}					t_main;

#endif
