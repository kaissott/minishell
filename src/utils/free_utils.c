#include "../../includes/minishell.h"

void	free_expand_lst(t_expand **expand_lst)
{
	t_expand	*current;
	t_expand	*next;

	if (!expand_lst || !*expand_lst)
		return ;
	current = *expand_lst;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*expand_lst = NULL;
}

void	free_main_struct(t_main **main_struct)
{
	if ((*main_struct)->env)
		free_env_lst(&(*main_struct)->env);
	if ((*main_struct)->token)
		free_token_lst(&(*main_struct)->token);
	if ((*main_struct)->exec)
		free_exec_lst(&(*main_struct)->exec);
	(*main_struct)->error.error_type = ERR_NONE;
	(*main_struct)->error.unexpected_token = '\0';
}

void	clear_and_exit(t_main *main_struct, ssize_t errcode)
{
	if (errcode != ERR_NONE)
	{
		print_token_error_msg(main_struct->error.error_type, main_struct->error.unexpected_token);
		free_main_struct(&main_struct);
		free(main_struct);
	}
	exit(errcode);
}
