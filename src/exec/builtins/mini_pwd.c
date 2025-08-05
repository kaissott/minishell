/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:56:24 by karamire          #+#    #+#             */
/*   Updated: 2025/07/30 21:36:26 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pwd(void)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		perror("minishell: pdw: ");
	ft_putendl_fd(path, STDOUT_FILENO);
	return (true);
}
