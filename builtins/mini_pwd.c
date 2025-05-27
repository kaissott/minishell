/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:56:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/26 19:18:54 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	pwd(t_main *main, int fd)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		return (0);
	ft_putstr_fd(path, fd);
	write(fd, "\n", 1);
	return (1);
}
