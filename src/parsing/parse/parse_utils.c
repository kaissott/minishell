/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:29:30 by ludebion          #+#    #+#             */
/*   Updated: 2025/09/02 03:02:52 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**resize_cmd_args(char **cmd, char *new_arg)
{
	size_t	len;
	char	**new_cmd;

	len = 0;
	while (cmd && cmd[len])
		len++;
	new_cmd = ft_calloc(len + 2, sizeof(char *));
	if (!new_cmd)
		return (NULL);
	if (cmd)
		ft_memcpy(new_cmd, cmd, len * sizeof(char *));
	new_cmd[len] = ft_strdup(new_arg);
	if (!new_cmd[len])
		return (NULL);
	free(cmd);
	return (new_cmd);
}

void	process_exec_std(t_shell *shell, t_token *token, t_exec *new_cmd,
		int std)
{
	if (token->next->is_blank || token_contains_ifs_chunks(shell, token->next))
	{
		reset_std_file(shell, token, std, new_cmd);
		return ;
	}
	if (std == STDIN_FILENO)
	{
		new_cmd->infile.fd = open_file(token->next->value, token->type);
		if (new_cmd->infile.fd == -1)
		{
			secure_close(&new_cmd->infile.fd_heredoc, STDIN_FILENO);
			set_error_syntax(&shell->error, ERR_PREV_OPEN, '\0', NULL);
			print_perror(token->next->value);
		}
	}
	else
	{
		new_cmd->outfile.fd = open_file(token->next->value, token->type);
		if (new_cmd->outfile.fd == -1)
		{
			set_error_syntax(&shell->error, ERR_PREV_OPEN, '\0', NULL);
			print_perror(token->next->value);
		}
	}
}
