/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 02:56:24 by kaissramire       #+#    #+#             */
/*   Updated: 2025/03/26 03:21:36 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	pwd()
{
	char	path[1024];
	if (getcwd(path, 1024) == NULL)
		return(0);
	ft_putstr_fd(path, 1);
	write(1, "\n", 1);
	return(1);
}

int	pwd_parsing(t_cmd *cmd)
{
	if(cmd->next != NULL)
		ft_putendl_fd("pwd: too many arguments", 2);
	if(!pwd())
		exit(1);
	return(1);
}

int main(void)
{
	pwd();
	return(0);
}
