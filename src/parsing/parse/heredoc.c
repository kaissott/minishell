/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 22:52:01 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/23 00:12:09 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// t_parse_error	create_heredoc(t_exec *new_cmd)
// {
// 	int	i;

// 	i = 0;
// 	if (create_heredoc_filepath(new_cmd, i) != ERR_NONE)
// 		return (ERR_MALLOC);
// 	new_cmd->infile.fd = open(new_cmd->infile.filepath,
// 			O_CREAT | O_EXCL | O_WRONLY, 0644);
// 	while ((new_cmd->infile.fd == -1 && errno == EEXIST))
// 	{
// 		free(new_cmd->infile.filepath);
// 		new_cmd->infile.filepath = NULL;
// 		i++;
// 		if (create_heredoc_filepath(new_cmd, i) != ERR_NONE)
// 			return (ERR_MALLOC);
// 		new_cmd->infile.fd = open(new_cmd->infile.filepath,
// 				O_CREAT | O_EXCL | O_WRONLY, 0644);
// 	}
// 	if (new_cmd->infile.fd == -1 && errno != EEXIST)
// 	{
// 		print_perror(new_cmd->infile.filepath);
// 		return (ERR_OPEN);
// 	}
// 	return (ERR_NONE);
// }

// static void	write_in_heredoc(t_parse_error *errcode, int *fd_heredoc,
// 		const char *delimiter)
// {
// 	char	*rl;
// 	char	*line;

// 	while (1)
// 	{
// 		rl = NULL;
// 		if (isatty(STDIN_FILENO))
// 		{
// 			rl = readline("heredoc> ");
// 		}
// 		else
// 		{
// 			line = get_next_line(fileno(stdin));
// 			rl = ft_strtrim(line, "\n");
// 			free(line);
// 		}
// 		if (g_sig_mode == SIGINT)
// 		{
// 			free(rl);
// 			*errcode = ERR_SIG;
// 			break ;
// 		}
// 		if (!rl)
// 		{
// 			printf("minishell: warning : \"here-document\" delimited by end of file (instead of \"%s\")\n",
// 				delimiter);
// 			break ;
// 		}
// 		if (ft_strcmp(rl, delimiter) == 0)
// 		{
// 			free(rl);
// 			break ;
// 		}
// 		if (ft_putendl_fd(rl, *fd_heredoc) == -1)
// 		{
// 			print_perror("Write");
// 			*errcode = ERR_SIG;
// 		}
// 		free(rl);
// 	}
// }

// t_parse_error	handle_in_heredoc(int *fd_heredoc, const char *delimiter)
// {
// 	t_parse_error	errcode;

// 	rl_event_hook = rl_hook;
// 	errcode = ERR_NONE;
// 	init_sigaction_hd();
// 	write_in_heredoc(&errcode, fd_heredoc, delimiter);
// 	rl_event_hook = NULL;
// 	init_sigaction();
// 	if (secure_close(fd_heredoc) != ERR_NONE)
// 		return (ERR_CLOSE);
// 	return (errcode);
// }
