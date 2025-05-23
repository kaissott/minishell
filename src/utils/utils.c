/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 01:36:17 by luca              #+#    #+#             */
/*   Updated: 2025/05/23 04:36:18 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*char_realloc(char *s, char c)
{
	char	*str;
	size_t	s_len;

	if (!s)
	{
		str = ft_calloc(2, sizeof(char));
		if (!str)
			return (NULL);
		str[0] = c;
		return (str);
	}
	s_len = ft_strlen(s);
	str = ft_calloc(s_len + 2, sizeof(char));
	if (!str)
		return (NULL);
	str = ft_memcpy(str, s, s_len);
	str[s_len] = c;
	free(s);
	return (str);
}

bool	check_file(char *file)
{
	if (access(file, R_OK) == -1)
		return (false);
	return (true);
}

void	free_lst_token(t_token **lst_token)
{
	t_token	*tmp;

	while (*lst_token)
	{
		tmp = (*lst_token)->next;
		free((*lst_token)->value);
		free(*lst_token);
		*lst_token = tmp;
	}
}
