/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:49:29 by karamire          #+#    #+#             */
/*   Updated: 2025/06/13 16:32:53 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

// void	free_files(t_main *main)
// {
// 	int	i;

// 	if (main->node->outfile.fd != NULL)
// 	{
// 		free(main->node->infile.fd);
// 	}
// 	if (main->node->infile.fd != NULL)
// 	{
// 		if (ft_strncmp(main->node->infile.fd, "./tmp/here_doc", 14) == 0)
// 		{
// 			printf("oui %s\n", main->node->infile.fd);
// 			if (access(main->node->infile.fd, F_OK) == -1)
// 				perror("access failed before unlink");
// 			if (unlink(main->node->infile.fd) == -1)
// 				perror("unlink failed");
// 			free(main->node->infile.fd);
// 		}
// 		else
// 		{
// 			printf("non");
// 			free(main->node->infile.fd);
// 		}
// 	}
// }
void	free_tabs(char **tab1, char **tab2)
{
	int	i;

	i = 0;
	if (tab1)
	{
		while (tab1[i])
		{
			free(tab1[i]);
			i++;
		}
	}
	i = 0;
	if (tab2)
	{
		while (tab2[i])
			free(tab2[i++]);
	}
}
