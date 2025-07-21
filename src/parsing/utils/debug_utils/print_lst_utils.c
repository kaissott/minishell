/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:34:01 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/19 02:53:45 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	print_info_token(t_token *lst)
{
	size_t			i;
	t_token_chunk	*tmp;

	i = 1;
	while (lst)
	{
		printf("Token node [%zu]\n", i++);
		if (lst->value)
			printf("\tvalue: [%s] ", lst->value);
		else
			printf("\tvalue: [NULL] ");
		printf("type: [%d] is_delimiter : [%d]\n", lst->type,
			lst->is_delimiter);
		if (lst->chunks)
		{
			tmp = lst->chunks;
			while (tmp)
			{
				printf("\tchunk value: [%s] type : [%d] is_expanded : [%d]\n",
					tmp->value, tmp->type, tmp->is_expanded);
				tmp = tmp->next;
			}
		}
		lst = lst->next;
	}
}

void	print_token_lst(t_token *lst, char *msg)
{
	t_token	*tmp;

	printf("\n%s\n", msg);
	if (!lst)
	{
		printf("The token list is empty\n");
		return ;
	}
	tmp = lst;
	print_info_token(tmp);
}

void	print_chunk_lst(t_token_chunk *lst, char *msg)
{
	size_t			i;
	t_token_chunk	*tmp;

	i = 1;
	printf("\n%s\n", msg);
	if (!lst)
	{
		printf("The chunk list is empty\n");
		return ;
	}
	tmp = lst;
	while (tmp)
	{
		printf("Node [%zu] :\n", i++);
		if (tmp->value)
			printf("\tvalue : %s\n", tmp->value);
		else
			printf("\tNo chunk value\n");
		printf("\ttype : %d\n", tmp->type);
		tmp = tmp->next;
	}
}

static void	print_info_exec(t_exec *lst)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (lst)
	{
		printf("Node [%zu]\n", i++);
		if (lst->cmd)
		{
			j = 0;
			while (lst->cmd[j])
			{
				printf("\tcmd[%zu]: [%s]\n", j, lst->cmd[j]);
				j++;
			}
		}
		if (lst->infile.filepath)
			printf("\tinfile filepath : %s\n", lst->infile.filepath);
		printf("\tfd : [%d] type : [%d]\n", lst->infile.fd, lst->infile.type);
		if (lst->outfile.filepath)
			printf("\toutfile filepath : %s\n", lst->outfile.filepath);
		printf("\tfd : [%d] type : [%d]\n", lst->outfile.fd, lst->outfile.type);
		lst = lst->next;
	}
}

void	print_exec_lst(t_exec *lst, char *msg)
{
	t_exec	*tmp;

	printf("\n%s\n", msg);
	if (!lst)
	{
		ft_putstr_fd("The list is empty\n", STDOUT_FILENO);
		return ;
	}
	tmp = lst;
	print_info_exec(tmp);
}
