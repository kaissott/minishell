#include "../../includes/minishell.h"

char	**env_to_tab(t_main *main)
{
	int		i;
	int		j;
	char	**tab;
	t_env	*tmp;

	i = 0;
	tmp = main->env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		free_and_exit_error(main, ERR_MEM, 12);
	tmp = main->env;
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
