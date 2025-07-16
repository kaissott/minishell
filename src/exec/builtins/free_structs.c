
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:09:40 by karamire          #+#    #+#             */
/*   Updated: 2025/06/17 18:30:38 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_env(t_main *main)
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

void	free_node(t_main *main)
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
void	here_doc_unlink(t_file infile)
{
	if (infile.is_heredoc == true)
	{
		unlink(infile.filepath);
		return ;
	}
}
void	close_node(t_main *main)
{
	t_exec	*temp;

	temp = main->exec;
	while (temp != NULL)
	{
		exit_error_two_close(main, temp->infile.fd, temp->outfile.fd);
		if (temp->infile.filepath)
		{
			here_doc_unlink(temp->infile);
			free(temp->infile.filepath);
		}
		if (temp->outfile.filepath)
			free(temp->outfile.filepath);
		temp = temp->next;
	}
}

int	free_struct(t_main *main)
{
	if (main->env != NULL)
		free_env(main);
	if (main->exec != NULL)
		free_node(main);
}
void	free_tab_2(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}
void	free_and_exit_error(t_main *main, char *tmp, char *error,
		int err_number)
{
	if (tmp != NULL)
		free(tmp);
	if (main->env_tab)
		free(main->env_tab);
	exit_error_minishell(main, err_number, error);
}
int	set_return_err_code(t_main *main, char *error, int err_number)
{
	perror(error);
	main->errcode = err_number;
	return (err_number);
}
