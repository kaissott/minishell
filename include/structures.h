/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 03:04:19 by luca              #+#    #+#             */
/*   Updated: 2025/06/10 00:18:55 by kaissramire      ###   ########.fr       */
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

typedef struct s_file
{
	int					fd;
	t_token_type		type;
}						t_file;

typedef struct s_lst_node
{
	char				**cmd;
	t_file				infile;
	t_file				outfile;
	struct s_lst_node	*next;
}						t_lst_node;

typedef struct s_env
{
	char				*env;
	struct s_env		*next;
}						t_env;

typedef struct s_main
{
	t_env				*mainenv;
	t_lst_node			*node;
	int					error;
}						t_main;

#endif
