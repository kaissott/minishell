/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:38:41 by karamire          #+#    #+#             */
/*   Updated: 2025/08/27 08:25:51 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_unescape(char *s)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	res = ft_calloc(strlen(s) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\\')
		{
			i++;
			if (s[i] == 'n')
				res[j++] = '\n';
			else if (s[i] == 't')
				res[j++] = '\t';
			else
				res[j++] = s[i];
			i++;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

void	export_new_var(t_shell *main, char *var)
{
	int		i;
	char	*new;
	t_env	*export;

	i = 0;
	while (var[i] != '=')
		i++;
	if (ft_strncmp("IFS", var, i) == 0)
		new = ft_unescape(var);
	else
		new = ft_strdup(var);
	if (!new)
		free_and_exit_error(main, NULL, ERR_MEM, 12);
	export = lstnew_env(new, main);
	lstadd_back_env(&main->env, export);
}

void	replace_var(t_shell *main, char *var, t_env *env, bool is_ifs)
{
	char	*new;

	if (is_ifs)
		new = ft_unescape(var);
	else
		new = ft_strdup(var);
	if (!new)
		free_and_exit_error(main, NULL, ERR_MEM, 12);
	free(env->env);
	env->env = new;
}
