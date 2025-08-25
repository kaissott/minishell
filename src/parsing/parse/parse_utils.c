/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 02:29:30 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/25 21:53:55 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFF 4096
#define PIPE_SIZE 65536

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

t_parse_error	process_exec_std(t_shell *shell, t_token *token,
		t_exec *new_cmd, int std)
{
	if (token->next->is_blank || token_contains_ifs_chunks(token->next))
		return (reset_std_file(shell, token, std, new_cmd));
	if (std == STDIN_FILENO)
	{
		new_cmd->infile.filepath = ft_strdup(token->next->value);
		if (!new_cmd->infile.filepath)
			return (ERR_MALLOC);
		new_cmd->infile.fd = open_file(token->next->value, token->type);
		if (new_cmd->infile.fd == -1)
		{
			set_error_syntax(&shell->error, ERR_PREV_OPEN, '\0', NULL);
			print_perror(new_cmd->infile.filepath);
		}
		return (ERR_NONE);
	}
	new_cmd->outfile.filepath = ft_strdup(token->next->value);
	if (!new_cmd->outfile.filepath)
		return (ERR_MALLOC);
	new_cmd->outfile.fd = open_file(token->next->value, token->type);
	if (new_cmd->outfile.fd == -1)
	{
		set_error_syntax(&shell->error, ERR_PREV_OPEN, '\0', NULL);
		print_perror(new_cmd->outfile.filepath);
	}
	return (ERR_NONE);
}

t_parse_error	create_heredoc(t_exec *new_cmd)
{
	int	i;

	i = 0;
	if (create_heredoc_filepath(new_cmd, i) != ERR_NONE)
		return (ERR_MALLOC);
	new_cmd->infile.fd = open(new_cmd->infile.filepath,
			O_CREAT | O_EXCL | O_WRONLY, 0644);
	while ((new_cmd->infile.fd == -1 && errno == EEXIST))
	{
		free(new_cmd->infile.filepath);
		new_cmd->infile.filepath = NULL;
		i++;
		if (create_heredoc_filepath(new_cmd, i) != ERR_NONE)
			return (ERR_MALLOC);
		new_cmd->infile.fd = open(new_cmd->infile.filepath,
				O_CREAT | O_EXCL | O_WRONLY, 0644);
	}
	if (new_cmd->infile.fd == -1 && errno != EEXIST)
	{
		print_perror(new_cmd->infile.filepath);
		return (ERR_OPEN);
	}
	unlink(new_cmd->infile.filepath);
	return (ERR_NONE);
}

static void	write_in_heredoc(t_parse_error *errcode, t_exec *new_cmd,
		int *fd_heredoc, const char *delimiter)
{
	char	*rl;
	char	*line;
	size_t	used;
	size_t	n;
	size_t	to_write;

	used = 0;
	while (1)
	{
		rl = NULL;
		if (isatty(STDIN_FILENO))
		{
			rl = readline("heredoc> ");
		}
		else
		{
			line = get_next_line(fileno(stdin));
			rl = ft_strtrim(line, "\n");
			free(line);
		}
		if (g_sig_mode == SIGINT)
		{
			free(rl);
			*errcode = ERR_SIG;
			// printf("Closing read fd: %d\n", new_cmd->fd_heredoc);
			if (secure_close(&new_cmd->fd_heredoc) != ERR_NONE)
				*errcode = ERR_CLOSE;
			break ;
		}
		if (!rl)
		{
			printf("minishell: warning : \"here-document\" delimited by end of file (instead of \"%s\")\n",
				delimiter);
			break ;
		}
		if (ft_strcmp(rl, delimiter) == 0)
		{
			free(rl);
			break ;
		}
		n = ft_strlen(rl);
		to_write = n + 1;
		if (used + to_write > 65536)
		{
			close(*fd_heredoc);
		}
		else if (ft_putendl_fd(rl, *fd_heredoc) == -1)
		{
			print_perror("Write");
			*errcode = ERR_SIG;
			break ;
		}
		used += to_write;
		free(rl);
	}
}

t_parse_error	handle_in_heredoc(t_exec *new_cmd, int *fd_heredoc,
		const char *delimiter)
{
	t_parse_error	errcode;

	rl_event_hook = rl_hook;
	errcode = ERR_NONE;
	init_sigaction_hd();
	write_in_heredoc(&errcode, new_cmd, fd_heredoc, delimiter);
	rl_event_hook = NULL;
	init_sigaction();
	// printf("Closing write fd: %d\n", *fd_heredoc);
	if (secure_close(fd_heredoc) != ERR_NONE)
		return (ERR_CLOSE);
	return (errcode);
}
