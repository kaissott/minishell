/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:49:29 by karamire          #+#    #+#             */
/*   Updated: 2025/05/22 17:19:00 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/main.h"

void	free_files(t_main *main)
{
	int	i;

	if (main->node->outfile.filename != NULL)
	{
		free(main->node->infile.filename);
	}
	if (main->node->infile.filename != NULL)
	{
		if (ft_strncmp(main->node->infile.filename, "./tmp/here_doc", 14) == 0)
		{
			printf("oui %s\n", main->node->infile.filename);
			if (access(main->node->infile.filename, F_OK) == -1)
				perror("access failed before unlink");
			if (unlink(main->node->infile.filename) == -1)
				perror("unlink failed");
			free(main->node->infile.filename);
		}
		else
		{
			printf("non");
			free(main->node->infile.filename);
		}
	}
}
void	free_tabs(char **tab1, char **tab2)
{
	int	i;

	i = 0;
	if (tab1[i])
	{
		while (tab1[i])
			free(tab1[i++]);
	}
	i = 0;
	if (tab2[i])
	{
		while (tab2[i])
			free(tab2[i++]);
	}
}
