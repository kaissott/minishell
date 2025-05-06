/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:17:16 by karamire          #+#    #+#             */
/*   Updated: 2025/05/06 16:01:00 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins/builtins.h"

t_node	*node_create(char *arg, char *input, char *output)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->arg = arg;
	new_node->fd_in = input;
	new_node->fd_out = output;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
int	exec_tree(t_node *node)
{
	if (!node)
		return (0);
	printf("%s", node->arg);
	exec_tree(node->left);
	exec_tree(node->right);
	if (ft_strncmp(node->arg, "echo", 4) == 0)
		printf(" --> coucou\n");
	else
		printf("\n");
}
int	main(void)
{
	t_node	*node;
	char	*str;

	str = "<input <input2 <input3 ls -l | grep test && cat -e | head -2";
	node = node_create("&&", NULL, NULL);
	node->left = node_create("|", NULL, NULL);
	node->left->left = node_create("ls -l", NULL, NULL);
	node->left->right = node_create("grep test", NULL, NULL);
	node->right = node_create("|", NULL, NULL);
	node->right->left = node_create("echo test test", NULL, NULL);
	node->right->right = node_create("head -2", NULL, NULL);
	exec_tree(node);
}
