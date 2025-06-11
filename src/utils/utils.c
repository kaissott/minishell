#include "../../includes/minishell.h"

ssize_t	set_error(t_error *error, t_parse_error error_type,
		char unexpected_token)
{
	error->error_type = error_type;
	if (unexpected_token)
		error->unexpected_token = unexpected_token;
	return (error_type);
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

char	*join_or_dup(char *prev, char *next)
{
	char	*new_val;

	if (prev)
		new_val = ft_strjoin(prev, next);
	else
		new_val = ft_strdup(next);
	free(prev);
	return (new_val);
}

int	secure_open(int *fd, const char *filepath)
{
	if (!fd || !filepath)
		return (-1);
	*fd = open(filepath, O_RDONLY);
	if (*fd == -1)
	{
		perror("open");
		return (-1);
	}
	return (0);
}

int	secure_close(int *fd)
{
	if (!fd || *fd < 0)
		return (0);
	if (close(*fd) == -1)
	{
		perror("close");
		return (-1);
	}
	*fd = -1;
	return (0);
}
