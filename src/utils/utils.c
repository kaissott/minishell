#include "../../includes/minishell.h"

char	*get_token_error_msg(int err_code)
{
	if (err_code == MISSING_SINGLE_QUOTE)
		return ("Missing single quote (').");
	else if (err_code == MISSING_DOUBLE_QUOTE)
		return ("Missing double quote (\").");
	else if (err_code == T_DOUBLE_PIPE_ERROR)
		return ("Double pipe.");
	else if (err_code == -1)
		return ("Token creation failed (malloc error).");
	else
		return (NULL);
}

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
	ft_memcpy(str, s, s_len);
	str[s_len] = c;
	free(s);
	return (str);
}

int	check_file(char *filename, t_token_type file_type)
{
	if (file_type == T_REDIR_IN)
	{
		if (access(filename, R_OK) == -1)
			return (-1);
		return (open(filename, O_RDONLY));
	}
	else if (file_type == T_REDIR_TRUNC)
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (file_type == T_REDIR_APPEND)
		return (open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (-1);
}

void	free_lst(t_lst_node **lst)
{
	t_lst_node	*tmp;
	size_t		i;

	while (*lst)
	{
		i = 0;
		tmp = (*lst)->next;
		if ((*lst)->cmd)
		{
			while ((*lst)->cmd[i])
			{
				free((*lst)->cmd[i]);
				i++;
			}
			free((*lst)->cmd);
		}
		free(*lst);
		*lst = tmp;
	}
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
