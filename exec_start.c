/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 00:14:05 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/24 00:18:37 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/main.h"

int	start_exec(t_main *main)
{
	if (main->node->next != NULL)
		init_pipe_exec(main);
	else
		init_simple_cmd(main);
	return (errno);
}
