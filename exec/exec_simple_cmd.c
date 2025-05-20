/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:40:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/20 22:35:02 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_outfile_simple_cmd(t_main *main)
{
	int			fd_out;
	t_lst_node	*temp;

	temp = main->node;
	if (temp->outfile->file != NULL)
	{
		if (temp->outfile->)
		fd_out = open(temp->infile, O_RDONLY);
		if (fd_out < 0)
			exit_exec(main);
		return (fd_out);
	}
	else
		return (0);
}

int	get_infile_simple_cmd(t_main *main)
{
	int			fd_in;
	t_lst_node	*temp;

	temp = main->node;
	if (temp->infile != NULL)
	{
		fd_in = open(temp->infile, O_RDONLY);
		if (fd_in < 0)
			exit_exec(main);
		return (fd_in);
	}
	else
		return (0);
}

exec_simple_cmd(t_main *main)
{
	int	fd_in;
	int	fd_out;

	if (fork() != -1)
	{
		fd_in = get_infile_simple_cmd(main);
		fd_out = get_outfile_simple_cmd(main);
		exec_simple_cmd(main);
	}
}
