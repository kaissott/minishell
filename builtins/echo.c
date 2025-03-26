/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:08:11 by karamire          #+#    #+#             */
/*   Updated: 2025/03/26 02:56:00 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo_printing(t_cmd *echo)
{
	t_cmd *temp;

	temp = echo;
	while(temp)
	{
		ft_putstr_fd(temp->content, 1);
		if(temp->next != NULL)
			write(1, " ", 1);
		temp = temp->next;
	}
}
char	*echo_parsing(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	i = 0;
	if (ft_strcmp(cmd->next->content, "-n") == 0)
	{
		temp = cmd->next->next;
		i = 1;
	}
	else
		temp = cmd->next;
	echo_printing(temp);
	if (i == 0)
		write(1, "\n", 1);
}

int	main(void)
{
	t_cmd	*cmd;

	cmd = lstnew("echo");
	lstadd_back(&cmd, lstnew("-n"));
	lstadd_back(&cmd, lstnew("coucou"));
	lstadd_back(&cmd, lstnew("coucou            bb"));
	echo_parsing(cmd);
	return (0);
}
