/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:11:54 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/24 23:03:05 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include "structures.h"

t_parse_error	parsing(t_shell *shell);
char			**resize_cmd_args(char **cmd, char *new_arg);
t_parse_error	process_exec_std(t_token *token, t_exec *new_cmd, int std);
t_parse_error	create_heredoc(t_exec *new_node);
int				handle_in_heredoc(int *fd_heredoc,
					const char *next_token_value);

#endif
