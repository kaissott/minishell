/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:34:52 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/12 23:37:11 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct s_node
{
	char			*arg;
	char			*fd_in;
	char			*fd_out;
}					t_node;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}					t_env;

typedef struct s_main
{
	t_env			*mainenv;
	t_node			*node;
}					t_main;
