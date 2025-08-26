/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:11:54 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/26 09:43:44 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include "structures.h"

t_parse_error	preprocess(t_shell *shell);
t_parse_error	check_heredoc(size_t *bytes_write, char *line, t_exec *new_cmd,
					int *pipe_write);
bool			check_line(char *line, char *delimiter);

t_parse_error	parsing(t_shell *shell);
char			**resize_cmd_args(char **cmd, char *new_arg);
void			process_exec_std(t_shell *shell, t_token *token,
					t_exec *new_cmd, int std);

#endif
