/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:14:31 by karamire          #+#    #+#             */
/*   Updated: 2025/06/02 20:19:06 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	create_node(t_main *main, char *line)
{
	t_lst_node	*node;
	t_lst_node	*node2;

	node = malloc(sizeof(t_lst_node));
	node2 = malloc(sizeof(t_lst_node));
	main->node = node;
	main->node->cmd = ft_split(line, ' ');
	main->node->infile.fd = open("Makefile", O_RDONLY);
	main->node->outfile.fd = STDOUT_FILENO;
	main->node->outfile.type = T_REDIR_TRUNC;
	main->node->next = node2;
	node2->cmd = malloc(sizeof(char *) * 3);
	node2->cmd[0] = ft_strdup("head");
	node2->cmd[1] = "-2";
	node2->cmd[2] = NULL;
	node2->infile.fd = 1;
	node2->outfile.fd = open("0ut", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	main->node->next->next = NULL;
	return (0);
}
