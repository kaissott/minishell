/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:56:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/03/30 18:19:03 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd(void)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		return (0);
	ft_putstr_fd(path, 1);
	write(1, "\n", 1);
	return (1);
}

int	pwd_parsing(t_cmd *cmd)
{
	// printf("%s", cmd->flag);
	if (cmd->flag != NULL)
		ft_putendl_fd("pwd: too many arguments", 2);
	else if (!pwd())
		exit(1);
	return (1);
}

// int main(void)
// {
// 	pwd();
// 	return(0);
// }
