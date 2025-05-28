/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:24:55 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/29 00:55:35 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	export_new_var(t_main *main, char *var)
{
	int		i;
	char	*new;

	i = 0;
	while (var[i] != '=')
		i++;
	new = ft_strdup(var);
	lstadd_back(&main->mainenv, lstnew(new));
}
int	mini_export(t_main *main)
{
	int		i;
	char	**tab;

	tab = ft_split(main->node->cmd, ' ');
	i = 1;
	if (tab[1] == NULL)
		return (0);
	while (tab[i])
	{
		if (ft_strchr(tab[i], '=') != NULL)
			export_new_var(main, tab[i]);
		i++;
	}
}
