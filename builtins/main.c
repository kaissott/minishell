/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:02:37 by karamire          #+#    #+#             */
/*   Updated: 2025/04/24 16:25:20 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cmd_checker(t_cmd *cmd, char **env)
{
	t_env	*mainenv;

	mainenv = env_build(env);
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		mini_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		pwd_parsing(cmd);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		env_print(mainenv);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		export_parsing(cmd, mainenv);
	else
		printf("command not found");
	return (0);
}
int	main(int ac, char **av, char **env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * 4);
	cmd->cmd = av[1];
	cmd->args[0] = av[2];
	cmd->args[1] = av[3];
	cmd->args[2] = av[4];
	cmd->args[3] = NULL;
	cmd->flag = NULL;
	cmd_checker(cmd, env);
	return (0);
}
