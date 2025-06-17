#include "../../includes/minishell.h"

void	no_env_build(t_main *main)
{
	char	buff[1024];
	char	*pwd;
	char	*shlvl;
	t_env	*mainenv;

	mainenv = malloc(sizeof(t_env));
	if (!mainenv)
		free_and_exit_error(main, ERR_MEM, 12);
	getcwd(buff, 1024);
	pwd = ft_strjoin("PWD=", buff);
	if (!pwd)
		free_and_exit_error(main, ERR_MEM, 12);
	mainenv = lstnew(pwd);
	if (!mainenv)
		free_and_exit_error(main, ERR_MEM, 12);
	mainenv->next = NULL;
	shlvl = ft_strdup("SHLVL=1");
	lstadd_back(&mainenv, lstnew(shlvl));
	main->env = mainenv;
}

void	env_build(char **env, t_main *main)
{
	int		i;
	char	*str;
	t_env	*mainenv;

	str = ft_strdup(env[0]);
	if (!str)
		free_and_exit_error(main, ERR_MEM, 12);
	mainenv = lstnew(str);
	if (!mainenv)
		handle_error_exit(ERR_MEM, 12);
	i = 1;
	while (env[i] != NULL)
	{
		str = ft_strdup(env[i]);
		if (!str)
			free_and_exit_error(main, ERR_MEM, 12);
		lstadd_back(&mainenv, lstnew(str));
		i++;
	}
	main->env = mainenv;
}

int	check_env_available(char **env, t_main *main)
{
	char	*str;
	t_env	*temp;

	str = getenv("PATH");
	if (str == NULL)
		no_env_build(main);
	else
		env_build(env, main);
	return (0);
}
