/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:56:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/31 20:42:05 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	pwd(t_main *main, int fd)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		return (0);
	ft_putendl_fd(path, fd);
	return (1);
}
