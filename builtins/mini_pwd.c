/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:56:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/02 16:35:41 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	pwd(t_main *main)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		return (0);
	ft_putendl_fd(path, STDOUT_FILENO);
	return (1);
}
