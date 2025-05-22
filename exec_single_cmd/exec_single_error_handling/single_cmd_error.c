/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:47:44 by karamire          #+#    #+#             */
/*   Updated: 2025/05/22 17:09:54 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	fork_error(t_main *main)
{
	int	i;

	printf("Fork failed");
	// free_tabs(main->mainenv, NULL);
	free_files(main);
}
