/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:09:40 by karamire          #+#    #+#             */
/*   Updated: 2025/08/27 02:23:27 by ludebion         ###   ########.fr       */
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
		if (head->env)
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
	t_exec	*tmp;

	tmp = main->exec;
	while (tmp != NULL)
	{
		ft_safe_close_node(tmp, &tmp->infile.fd, &tmp->outfile.fd);
		tmp = tmp->next;
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
