/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:20:44 by karamire          #+#    #+#             */
/*   Updated: 2025/06/15 23:57:28 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void	free_env(t_main *main);

void	print_ascii_logo(void)
{
	const char *red = "\033[1;31m";
	const char *reset = "\033[0m";

	printf("%s", red);
	printf("   _____  .__       .__       .__           .__  .__       _____ ________  \n");
	printf("  /     \\ |__| ____ |__| _____|  |__   ____ |  | |  |     /  |  |\\_____  \\ \n");
	printf(" /  \\ /  \\|  |/    \\|  |/  ___/  |  \\_/ __ \\|  | |  |    /   |  |_/  ____/ \n");
	printf("/    Y    \\  |   |  \\  |\\___ \\|   Y  \\  ___/|  |_|  |__ /    ^   /       \\ \n");
	printf("\\____|__  /__|___|  /__/____  >___|  /\\___  >____/____/ \\____   |\\_______ \\ \n");
	printf("       \\/        \\/        \\/     \\/     \\/                 |__|        \\/ \n");
	printf("            by Karamire and Ludebion\n");
	printf("%s", reset);
}

void	exit_error_init_minishell(t_main *main, int errcode)
{
	if (main)
	{
		free_struct(main);
		free(main);
	}
	exit(errcode);
}

t_main	*init_minishell(char **env)
{
	t_main	*main_struct;

	print_ascii_logo();
	main_struct = ft_calloc(1, sizeof(t_main));
	main_struct->env = NULL;
	if (!main_struct)
		exit_error_init_minishell(main_struct, errno);
	check_env_available(env, main_struct);
	main_struct->std_out = dup(STDOUT_FILENO);
	main_struct->std_in = dup(STDIN_FILENO);
	if (main_struct->std_out == -1 || main_struct->std_in == -1)
	{
		if (main_struct->std_out)
			close(main_struct->std_out);
		if (main_struct->std_in)
			close(main_struct->std_in);
		exit_error_init_minishell(main_struct, errno);
	}
	return(main_struct);
}
