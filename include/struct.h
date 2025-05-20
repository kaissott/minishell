/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:34:52 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/20 20:14:54 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <stdbool.h>



typedef struct s_lst_node
{
	char				*cmd;
	char				*infile;
	char				*outfile;
	bool				outfile_type;
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
}						t_main;

#endif
