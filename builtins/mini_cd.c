/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:57:04 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/02 20:53:20 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

void	env_pwd_update(t_main *main)
{
	t_env	*temp;
	char	*tmp;
	int		i;
	char	path[1024];

	i = 0;
	if (getcwd(path, 1024) == NULL)
		return ;
	temp = main->mainenv;
	while (ft_strstr(temp->env, "PWD=") != 1)
		temp = temp->next;
	if (temp->env != NULL)
	{
		free(temp->env);
		tmp = ft_strjoin("PWD=", path);
		if (!tmp)
			return ;
		temp->env = tmp;
	}
}

void	env_oldpwd_update(t_main *main)
{
	t_env	*temp;
	int		i;
	char	*path;
	char	pwd[1024];

	i = 0;
	temp = main->mainenv;
	if (getcwd(pwd, 1024) == NULL)
		return ;
	while (temp != NULL && ft_strstr(temp->env, "OLDPWD=") != 1)
		temp = temp->next;
	if (temp != NULL)
	{
		free(temp->env);
		temp->env = ft_strjoin("OLDPWD=", pwd);
	}
	else
	{
		path = ft_strjoin("OLDPWD=", pwd);
		lstadd_back((&main->mainenv), lstnew(path));
	}
}

bool	name_size_error(char *name, char *error)
{
	printf("bash: cd: %s%s", name, error);
	return (false);
}
int	dir_name_size(char *name, int *total_size)
{
	int	i;

	i = 0;
	while (name[i])
		i++;
	total_size = total_size + i + 1;
	if (i > 255)
		return (name_size_error(name, ERR_CD_NAMETOOLONG));
	return (true);
}
bool	check_path_size(char *path)
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
		if (dir_name_size(dir[i], &total_size) == false)
			printf("caca");
		i++;
	}
	if (total_size > 4096)
		return (name_size_error(dir[1], ERR_CD_NAMETOOLONG));
	return (true);
}
bool	mini_cd(char *line, t_main *main)
{
	char	**tab;

	env_oldpwd_update(main);
	tab = main->node->cmd;
	if (tab[1])
	{
		if (chdir(tab[1]) == -1)
			printf("nul");
	}
	else
	{
		if (chdir("~") == -1)
			printf("nul");
	}
	env_pwd_update(main);
	return (true);
}
