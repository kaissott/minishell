/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:11:47 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/27 07:23:22 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include "minishell.h"
# include "structures.h"

int				open_file(const char *filepath, t_token_type file_type);
t_parse_error	secure_close(int *fd, int std);
t_parse_error	check_std_cmd(int std, t_exec *new_cmd);
void			reset_std_file(t_shell *shell, t_token *token, int std,
					t_exec *new_cmd);
char			*create_heredoc_filepath(int i);

char			*join_or_dup(char *prev, char *next);
bool			is_dollar_alone(t_token_chunk *chunk, size_t i, size_t len,
					t_token_chunk *next);

#endif
