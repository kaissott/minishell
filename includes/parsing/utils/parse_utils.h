/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:11:47 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/26 08:06:17 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "minishell.h"
# include "structures.h"

int				open_file(const char *filepath, t_token_type file_type);
t_parse_error	secure_close(int *fd, int std);
t_parse_error	check_std_cmd(int std, t_exec *new_cmd);
void			reset_std_file(t_shell *shell, t_token *token, int std,
					t_exec *new_cmd);
char			*create_heredoc_filepath(int i);

bool			check_parsing(t_shell *shell, t_parse_error errcode,
					bool at_end);
char			*join_or_dup(char *prev, char *next);
bool			is_dollar_alone(t_token_chunk *chunk, size_t i, size_t len,
					t_token_chunk *next);

#endif
