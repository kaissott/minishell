#include "../../includes/minishell.h"

void	set_error(t_error *error, t_parse_error error_type,
		char unexpected_token)
{
	error->error_type = error_type;
	if (unexpected_token)
		error->unexpected_token = unexpected_token;
}

void	print_token_error_msg(t_parse_error err_code, char unexpected_token)
{
	if (err_code == ERR_MISSING_SINGLE_QUOTE)
		fprintf(stderr, "Missing single quote (').\n");
	else if (err_code == ERR_MISSING_DOUBLE_QUOTE)
		fprintf(stderr, "Missing double quote (\").\n");
	else if (err_code == ERR_UNEXPECTED_TOKEN)
	{
		if (!unexpected_token)
			fprintf(stderr, "%s `newline'\n",
				"syntax error near unexpected token ");
		else
			fprintf(stderr, "%s `%c'\n", "syntax error near unexpected token ",
				unexpected_token);
	}
	else if (err_code == ERR_DOUBLE_PIPE)
		fprintf(stderr, "Double pipe.\n");
	else if (err_code == ERR_MALLOC)
		fprintf(stderr, "Token creation failed (malloc error).\n");
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

void	free_lst(t_exec **lst_exec)
{
	t_exec	*tmp;
	size_t	i;

	while (*lst_exec)
	{
		i = 0;
		tmp = (*lst_exec)->next;
		if ((*lst_exec)->cmd)
		{
			while ((*lst_exec)->cmd[i])
			{
				free((*lst_exec)->cmd[i]);
				i++;
			}
			free((*lst_exec)->cmd);
		}
		free(*lst_exec);
		*lst_exec = tmp;
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
