/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:11:47 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 10:04:02 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "structures.h"

int				open_file(const char *filepath, t_token_type file_type);
t_parse_error	secure_close(int *fd);
t_parse_error	check_std_cmd(int std, t_exec *new_cmd);

bool			check_parsing(t_shell *shell, t_parse_error errcode,
					bool at_end);

t_parse_error	set_error(t_error *error, t_parse_error error_type,
					char unexpected_token, char *ambiguous_redir);
void			print_syntax_error_msg(t_parse_error errcode,
					char unexpected_token, char *ambiguous_redir);
char			*join_or_dup(char *prev, char *next);

#endif
