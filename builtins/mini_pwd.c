/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:56:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/20 19:25:54 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	pwd(void)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		return (0);
	ft_putstr_fd(path, 1);
	write(1, "\n", 1);
	return (1);
}
