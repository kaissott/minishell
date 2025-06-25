#include "../../../includes/minishell.h"

void	delete_env_node(t_env **env, char *var)
{
	t_env	*current;
	t_env	*temp;

	if (!env || !var)
		return ;
	current = *env;
	if (ft_strncmp(current->env, var, ft_strlen(var)) == 0
		&& (current->env[ft_strlen(var)]) == '=')
	{
		*env = current->next;
		free(current->env);
		free(current);
		return ;
	}
	while (current->next)
	{
		if (ft_strncmp(current->next->env, var, ft_strlen(var)) == 0
			&& (current->next->env[ft_strlen(var)]) == '=')
		{
			temp = current->next;
			current->next = temp->next;
			free(temp->env);
			free(temp);
			return ;
		}
		current = current->next;
	}
}

bool	mini_unset(t_main *main)
{
	char	**cmd;
	int		i;

	i = 1;
	cmd = main->exec->cmd;
	if (cmd[1] == NULL)
		return (0);
	if (cmd[1][0] == '-')
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd("': invalid option", 2);
		main->errcode = 2;
		return (0);
	}
	while (cmd[i])
	{
		delete_env_node(&main->env, cmd[i]);
		i++;
	}
	return (true);
}
