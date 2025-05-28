/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:52:10 by karamire          #+#    #+#             */
/*   Updated: 2025/05/28 21:32:42 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	env_print(t_main *main)
{
	t_env	*temp;

	temp = main->mainenv;
	while (temp)
	{
		ft_putstr_fd(temp->env, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		temp = temp->next;
	}
	return (0);
}
