/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:41:45 by karamire          #+#    #+#             */
/*   Updated: 2025/07/21 17:42:14 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
