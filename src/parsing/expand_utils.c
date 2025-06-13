#include "../../includes/minishell.h"

char	*get_var_value(t_env **env_lst, char *var_name)
{
	pid_t	pid;
	t_env	*tmp;

	pid = getpid();
	tmp = *env_lst;
	if (ft_strcmp(var_name, "$$") == 0)
		return (ft_itoa(pid));
	else if (ft_strcmp(var_name, "$?") == 0)
		return (ft_itoa(errno));
	else if (ft_strcmp(var_name, "$") == 0)
		return (ft_strdup("$"));
	while (tmp)
	{
		if (ft_strcmp(tmp->var, var_name) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
