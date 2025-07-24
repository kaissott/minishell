/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:09:40 by karamire          #+#    #+#             */
/*   Updated: 2025/07/24 23:27:29 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_shell *main)
{
	t_env	*head;
	t_env	*temp;

	head = main->env;
	while (head->next != NULL)
	{
		temp = head->next;
		free(head->env);
		free(head);
		head = temp;
	}
	free(head->env);
	free(head);
}

void	free_node(t_shell *main)
{
	t_exec	*temp;
	t_exec	*next;
	int		i;

	i = 0;
	temp = main->exec;
	while (temp != NULL)
	{
		next = temp->next;
		if (temp->cmd)
		{
			while (temp->cmd[i])
			{
				free(temp->cmd[i++]);
			}
			free(temp->cmd);
		}
		free(temp);
		temp = next;
		i = 0;
	}
	main->exec = NULL;
}

void	close_node(t_shell *main)
{
	t_exec	*temp;

	temp = main->exec;
	while (temp != NULL)
	{
		exit_error_two_close(main, temp->infile.fd, temp->outfile.fd);
		if (temp->infile.filepath)
			free(temp->infile.filepath);
		if (temp->outfile.filepath)
			free(temp->outfile.filepath);
		temp = temp->next;
	}
}

int	free_struct(t_shell *main)
{
	if (main->env != NULL)
		free_env(main);
	if (main->exec != NULL)
		free_node(main);
	return (1);
}
