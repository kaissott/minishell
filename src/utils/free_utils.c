#include "../../includes/minishell.h"

void	get_errcode(t_main *shell, t_parse_error errcode)
{
	if (errcode == ERR_MALLOC)
		shell->errcode = 12;
	else if (errcode >= ERR_SYNTAX && errcode <= ERR_MISSING_SINGLE_QUOTE)
		shell->errcode = 2;
	else if (errcode == ERR_TOKEN)
		shell->errcode = 1;
	else if (errcode >= ERR_CLOSE && errcode <= ERR_OPEN)
		shell->errcode = 1;
	else
		shell->errcode = 0;
}

void	free_shell(t_main *shell, t_parse_error errcode)
{
	// if (shell->env)
	// 	free_env_lst(&shell->env);
	if (shell->token)
		free_token_lst(&shell->token);
	if (shell->exec)
		free_exec_lst(&shell->exec);
	shell->error.error_type = ERR_NONE;
	shell->error.unexpected_token = '\0';
	// printf("shell->errcode after free shell : %d\n", shell->errcode);
}

void	clear_and_exit(t_main *shell, t_parse_error errcode)
{
	get_errcode(shell, errcode);
	print_token_error_msg(shell->error.error_type,
		shell->error.unexpected_token);
	free_shell(shell, errcode);
	free(shell);
}

bool	check_parsing(t_main *shell, t_parse_error errcode)
{
	get_errcode(shell, errcode);
	if (errcode == ERR_NONE)
		return (true);
	print_token_error_msg(errcode, shell->error.unexpected_token);
	free_shell(shell, errcode);
	return (false);
}
