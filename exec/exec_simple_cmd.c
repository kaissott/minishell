/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:40:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/21 02:19:34 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	exec_simple_cmd(t_main *main, int fd_in, int fd_out)
{
}

void	file_dup(int fd_in, int fd_out)
{
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
	}
	if (fd_out != 1)
	{
		dup2(fd_out, STDOUT_FILENO);
	}
}

int	get_outfile_simple_cmd(t_main *main)
{
	int			fd_out;
	t_lst_node	*temp;

	temp = main->node;
	if (temp->outfile.filename != NULL)
	{
		if (temp->outfile.type == T_REDIR_APPEND)
			fd_out = open(temp->outfile.filename, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else if (temp->outfile.type == T_REDIR_TRUNC)
			fd_out = open(temp->outfile.filename, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		// if (fd_out < 0)
		//	exit_exec(main);
		return (fd_out);
	}
	else
		return (1);
}

int	get_infile_simple_cmd(t_main *main)
{
	int			fd_in;
	t_lst_node	*temp;

	temp = main->node;
	if (temp->infile.filename != NULL)
	{
		fd_in = open(temp->infile.filename, O_RDONLY);
		if (fd_in < 0)
			dprintf(2, "infile crash\n");
		return (fd_in);
	}
	else
		return (0);
}

void	init_simple_cmd(t_main *main)
{
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	char	*argv[] = {"/usr/bin/wc", "Makefile", NULL};
	char	*envp[] = {NULL};

	pid = fork();
	if (pid == 0)
	{
		fd_in = get_infile_simple_cmd(main);
		fd_out = get_outfile_simple_cmd(main);
		file_dup(fd_in, fd_out);
		if (execve("/usr/bin/wc", argv, envp) == -1)
		{
			perror("execve");
		}
	}
	wait(NULL);
}

int	main(void)
{
	t_main		*main;
	t_lst_node	*node;

	node = malloc(sizeof(t_lst_node));
	main = malloc(sizeof(t_main));
	main->mainenv = NULL;
	main->node = node;
	main->node->cmd = NULL;
	main->node->infile.filename = NULL;
	main->node->outfile.filename = NULL;
	main->node->outfile.type = T_REDIR_APPEND;
	init_simple_cmd(main);
}
