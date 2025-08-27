/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 07:11:00 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/27 07:42:17 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_UTILS_H
# define SHELL_UTILS_H

# include "minishell.h"
# include "structures.h"

void			free_shell_error(t_shell *shell);

void			print_perror(char *error);
t_parse_error	set_error_syntax(t_error *error, t_parse_error error_type,
					char unexpected_token, char *ambiguous_redir);
void			print_syntax_error_msg(t_parse_error errcode,
					char unexpected_token, char *ambiguous_redir);
bool			check_parsing(t_shell *shell, t_parse_error errcode,
					bool at_end);

#endif
