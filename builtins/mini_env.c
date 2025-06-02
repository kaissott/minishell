/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:52:10 by karamire          #+#    #+#             */
/*   Updated: 2025/06/02 20:21:46 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

bool	env_print(t_main *main)
{
	t_env	*temp;

	temp = main->mainenv;
	while (temp)
	{
		ft_putstr_fd(temp->env, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		temp = temp->next;
	}
	return (true);
}
