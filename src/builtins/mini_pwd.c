/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:56:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/13 16:48:43 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	pwd(t_main *main)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		free_and_exit_error(main, ERR_GETCWD, errno);
	if (ft_putendl_fd(path, STDOUT_FILENO) == -1)
		free_and_exit_error(main, ERR_WRITE, errno);
	return (true);
}
