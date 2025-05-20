/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:40:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/20 20:12:08 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

get_infile_simple_cmd(t_lst_node *node)
{
	if (node->infile != NULL)
	{
		open(node->infile, O_RONDLY);
	}
}

exec_simple_cmd(t_main *main)
{
	t_lst_node	*temp;

	temp = main->node;
	if (fork() != -1)
	{
		get_infile_simple_cmd(temp);
		get_outfile_simple_cmd(temp);
		exec_simple_cmd(temp);
	}
}
