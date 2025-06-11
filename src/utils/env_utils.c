#include "../../includes/minishell.h"

static void	env_lst_add_back(t_env **env_lst, t_env *new_node)
{
	t_env	*tmp;

	if (!env_lst || !new_node)
		return ;
	if (!*env_lst)
	{
		*env_lst = new_node;
		return ;
	}
	tmp = *env_lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

bool	create_env_lst(t_env **env_lst, char **env)
{
	ssize_t	i;
	t_env	*new_env;
	char	*equal_sign;

	i = 0;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (!equal_sign)
		{
			i++;
			continue ;
		}
		new_env = ft_calloc(1, sizeof(t_env));
		if (!new_env)
			return (false);
		new_env->var = ft_substr(env[i], 0, equal_sign - env[i]);
		new_env->value = ft_strdup(equal_sign + 1);
		if (!new_env->var || !new_env->value)
			return (false);
		env_lst_add_back(env_lst, new_env);
		i++;
	}
	return (true);
}

void	print_env_lst(t_env *lst, char *msg)
{
	size_t	i;

	i = 1;
	printf("\n%s\n", msg);
	if (!lst)
	{
		printf("The env list is empty\n");
		return ;
	}
	while (lst)
	{
		printf("Node [%zu] :\n", i++);
		if (lst->var)
			printf("\tvar : %s\n", lst->var);
		else
			printf("\tnull var\n");
		if (lst->value)
			printf("\tvalue : %s\n", lst->value);
		else
			printf("\tNo value\n");
		lst = lst->next;
	}
}
