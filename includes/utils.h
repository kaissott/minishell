/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 07:11:00 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/24 07:47:53 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "structures.h"

int				rl_hook(void);
int				is_ascii_printable(const char *s);
void			print_perror(char *error);
t_parse_error	set_error(t_error *error, t_parse_error error_type,
					char unexpected_token, char *ambiguous_redir);
void			print_syntax_error_msg(t_parse_error errcode,
					char unexpected_token, char *ambiguous_redir);

#endif
