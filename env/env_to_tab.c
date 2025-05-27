/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:40:09 by karamire          #+#    #+#             */
/*   Updated: 2025/05/27 19:37:48 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

char	**env_to_tab(t_main *main)
{
	int		i;
	int		j;
	char	**tab;
	t_env	*tmp;

	i = 0;
	tmp = main->mainenv;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	tmp = main->mainenv;
	j = 0;
	while (i > 0)
	{
		tab[j] = tmp->env;
		tmp = tmp->next;
		i--;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_main	*main;
// 	t_env	*mainenv;

// 	main = malloc(sizeof(t_main));
// 	mainenv = env_build(env);
// 	main->mainenv = mainenv;
// 	env_to_tab(main);
// }
