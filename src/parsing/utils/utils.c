/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:31:24 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/26 10:21:03 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_shell(t_shell *shell, t_parse_error errcode)
{
	if (errcode == ERR_MALLOC && shell->env)
		free_env(shell);
	if (shell->token)
		free_token_lst(&shell->token);
	if (shell->exec)
		free_exec_lst(&shell->exec);
	shell->error.error_type = ERR_NONE;
	shell->error.unexpected_token = '\0';
	shell->error.ambiguous_redir = NULL;
}

static void	get_errcode(t_shell *shell, t_parse_error errcode)
{
	if (shell->error.error_type == ERR_PREV_OPEN)
		shell->errcode = 1;
	else if (errcode == ERR_AMBIGUOUS_REDIR)
		shell->errcode = 1;
	else if (errcode == ERR_MALLOC || errcode == ERR_PIPE)
		shell->errcode = 12;
	else if (errcode >= ERR_DOUBLE_PIPE && errcode <= ERR_MISSING_SINGLE_QUOTE)
		shell->errcode = 2;
	else if (errcode == ERR_TOKEN)
		shell->errcode = 1;
	else if (errcode >= ERR_READ && errcode <= ERR_OPEN)
		shell->errcode = 1;
	else
		shell->errcode = 0;
}

bool	check_parsing(t_shell *shell, t_parse_error errcode, bool at_end)
{
	if (errcode == ERR_NONE || errcode == ERR_AMBIGUOUS_REDIR
		|| shell->error.error_type == ERR_PREV_OPEN)
	{
		if (at_end || errcode == ERR_AMBIGUOUS_REDIR
			|| shell->error.error_type == ERR_PREV_OPEN)
			get_errcode(shell, errcode);
		shell->error.error_type = ERR_NONE;
		shell->error.ambiguous_redir = NULL;
		return (true);
	}
	get_errcode(shell, errcode);
	if (errcode != ERR_SIG && !(errcode >= ERR_READ && errcode <= ERR_OPEN)
		&& shell->error.error_type != ERR_PREV_OPEN)
		print_syntax_error_msg(errcode, shell->error.unexpected_token,
			shell->error.ambiguous_redir);
	free_shell(shell, errcode);
	if (errcode == ERR_MALLOC || errcode == ERR_PIPE)
	{
		free(shell);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
	else
		return (false);
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

bool	is_dollar_alone(t_token_chunk *chunk, size_t i, size_t len,
		t_token_chunk *next)
{
	if (len == 1 && chunk->value[i] == '$' && chunk->type != T_DOUBLE_QUOTED
		&& next && (next->type == T_SINGLE_QUOTED
			|| next->type == T_DOUBLE_QUOTED))
	{
		while (chunk->value[i])
		{
			chunk->value[i] = chunk->value[i + 1];
			i++;
		}
		return (true);
	}
	return (false);
}
