/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:11:56 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/24 07:56:58 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H

# include "minishell.h"
# include "structures.h"

t_parse_error	tokenisation(t_shell *shell, const char *cmd);
int				is_operator(const char *str);
t_token_type	get_token_type(t_error *error, const char *cmd);
void			set_heredocs_delimiters(t_shell *shell);

#endif
