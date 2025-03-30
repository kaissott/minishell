/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:02:37 by karamire          #+#    #+#             */
/*   Updated: 2025/03/30 18:19:07 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cmd_checker(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		mini_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		pwd_parsing(cmd);
	return (0);
}
int	main(int ac, char **av)
{
	t_cmd	*cmd;

	(void)ac;
	cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * 4);
	cmd->cmd = av[1];
	// printf("%s", cmd->cmd);
	cmd->flag = av[2];
	cmd->args[0] = av[3];
	// printf("%s", cmd->args[0]);
	cmd->args[1] = av[4];
	cmd->args[2] = av[5];
	cmd->args[3] = NULL;
	cmd_checker(cmd);
	// mini_echo(cmd);
	return (0);
}
