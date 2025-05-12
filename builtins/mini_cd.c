/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:57:04 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/10 21:25:01 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

int	dir_name_size(char *dir_name, int total_size)
{
	int	i;

	i = 0;
}
int	check_path_size(char *path)
{
	int		dir_size;
	int		total_size;
	int		i;
	char	**dir;

	i = 0;
	total_size = 0;
	dir = ft_split(path, '/');
	while (dir[i])
	{
		if (dir_name_size(dir[i], &total_size) == -1)
			return (-1);
		i++;
	}
	if (total_size > 4096)
		return (-1);
	return (0);
}
int	mini_cd(char *line)
{
	char	**tab;

	tab = ft_split(line, ' ');
	if (check_path_size(tab[1]) == false)
		return (-1);
	if (tab[1])
	{
		if (chdir(tab[1]) == -1)
			printf("nul");
	}
}
