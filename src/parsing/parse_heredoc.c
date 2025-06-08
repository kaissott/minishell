#include "../../includes/minishell.h"

void	print_lst_hd(t_heredoc *lst, char *msg)
{
	size_t	i;

	i = 1;
	printf("\n%s\n", msg);
	if (!lst)
	{
		printf("The hd list is empty\n");
		return ;
	}
	while (lst)
	{
		printf("Node [%zu] :\n", i++);
		if (lst->filepath)
			printf("filepath : %s ", lst->filepath);
		else
			printf("No filepath ");
		printf("fd : %d\n", lst->fd);
		lst = lst->next;
	}
}

int	write_in_heredoc(int *fd_heredoc, const char *next_token_value)
{
	char	*rl;

	while (1)
	{
		rl = readline("heredoc>");
		if (!rl)
		{
			secure_close(fd_heredoc);
			return (-1);
		}
		if (ft_strcmp(rl, next_token_value) == 0)
		{
			free(rl);
			break ;
		}
		ft_putendl_fd(rl, *fd_heredoc);
		free(rl);
	}
	return (0);
}

static void	heredoc_lst_add_back(t_heredoc **heredoc_lst, t_heredoc *new_node)
{
	t_heredoc	*tmp;

	if (!heredoc_lst || !new_node)
		return ;
	if (!*heredoc_lst)
	{
		*heredoc_lst = new_node;
		return ;
	}
	tmp = *heredoc_lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

int	create_heredoc_filepath(t_heredoc **heredoc_lst, t_heredoc *new_heredoc)
{
	int			heredoc_nbr;
	char		*heredoc_nbr_str;
	t_heredoc	*tmp;

	heredoc_nbr = 0;
	tmp = *heredoc_lst;
	while (tmp)
	{
		heredoc_nbr++;
		tmp = tmp->next;
	}
	heredoc_nbr_str = ft_itoa(heredoc_nbr);
	if (!heredoc_nbr_str)
		return (-1);
	new_heredoc->filepath = ft_strjoin("tmp/.ms_hd_", heredoc_nbr_str);
	free(heredoc_nbr_str);
	if (!new_heredoc->filepath)
	{
		free(new_heredoc);
		return (-1);
	}
	return (0);
}

t_heredoc	*create_heredoc(t_heredoc **heredoc_lst)
{
	t_heredoc	*new_heredoc;

	new_heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (!new_heredoc)
		return (NULL);
	if (create_heredoc_filepath(heredoc_lst, new_heredoc) == -1)
		return (NULL);
	new_heredoc->fd = -1;
	heredoc_lst_add_back(heredoc_lst, new_heredoc);
	return (new_heredoc);
}
