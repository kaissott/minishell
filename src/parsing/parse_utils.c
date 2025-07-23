/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:29:30 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 22:52:19 by karamire         ###   ########.fr       */
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

t_parse_error	process_exec_std(t_token *token, t_exec *new_cmd, int std)
{
	if (!token->next)
		return (ERR_AMBIGUOUS_REDIR);
	if (std == STDIN_FILENO)
	{
		new_cmd->infile.filepath = ft_strdup(token->next->value);
		if (!new_cmd->infile.filepath)
			return (ERR_MALLOC);
		new_cmd->infile.fd = open_file(token->next->value, token->type);
		if (new_cmd->infile.fd == -1)
			perror(new_cmd->infile.filepath);
	}
	else
	{
		new_cmd->outfile.filepath = ft_strdup(token->next->value);
		if (!new_cmd->outfile.filepath)
			return (ERR_MALLOC);
		new_cmd->outfile.fd = open_file(token->next->value, token->type);
		if (new_cmd->outfile.fd == -1)
			perror(new_cmd->outfile.filepath);
	}
	return (ERR_NONE);
}

t_parse_error	create_heredoc_filepath(t_exec **exec_lst, t_exec *new_node)
{
	int		i;
	char	*cmd_nbr;
	t_exec	*tmp;

	i = 0;
	tmp = *exec_lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	cmd_nbr = ft_itoa(i);
	if (!cmd_nbr)
		return (ERR_MALLOC);
	new_node->infile.filepath = ft_strjoin("/tmp/.ms_hd_", cmd_nbr);
	free(cmd_nbr);
	if (!new_node->infile.filepath)
		return (ERR_MALLOC);
	return (ERR_NONE);
}

int	test(void)
{
	return (0);
}

t_parse_error	write_in_heredoc(int *fd_heredoc, const char *next_token_value)
{
	char			*rl;
	t_parse_error	result;
	char			*line;

	rl_event_hook = test;
	result = ERR_NONE;
	init_sigaction_hd();
	while (1)
	{
		if (isatty(fileno(stdin)))
			rl = readline("heredoc > ");
		else
		{
			rl = get_next_line(fileno(stdin));
			if (rl)
			{
				line = ft_strtrim(rl, "\n");
				free(rl);
				rl = line;
			}
		}
		if (g_sig_mode > 0)
		{
			result = ERR_SIG;
			break ;
		}
		if (!rl)
			break ;
		if (ft_strcmp(rl, next_token_value) == 0)
		{
			free(rl);
			break ;
		}
		if (ft_putendl_fd(rl, *fd_heredoc) == -1)
			return (ERR_SIG);
		free(rl);
	}
	rl_event_hook = NULL;
	init_sigaction();
	if (secure_close(fd_heredoc) != ERR_NONE)
		return (ERR_CLOSE);
	return (result);
}
