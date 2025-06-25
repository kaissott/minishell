#include "../../includes/minishell.h"

t_parse_error	parsing_error(t_main *shell, t_parse_error errcode,
		char *filepath)
{
	// printf("errcode parsing error : %d\n", errcode);
	get_errcode(shell, errcode);
	free_shell(shell, errcode);
	if (filepath)
		perror(filepath);
	return (errcode);
}

t_parse_error	set_error(t_error *error, t_parse_error error_type,
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
	else if (err_code == ERR_SYNTAX)
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

	if (prev && next)
		new_val = ft_strjoin(prev, next);
	else if (prev)
		new_val = ft_strdup(prev);
	else if (next)
		new_val = ft_strdup(next);
	else
		new_val = ft_strdup("");
	free(prev);
	return (new_val);
}

void	check_open(int std)
{
	return ;
}
