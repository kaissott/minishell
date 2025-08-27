/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:11:50 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/27 06:22:16 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"
# include "structures.h"

t_parse_error	expansion(t_shell *shell);
t_expand		*extract_expand_var(char *var, ssize_t *i);
char			*get_var_value(t_shell *shell, char *var_name, bool *var_found);
t_parse_error	replace_chunk_value(t_shell *shell, t_expand **expand_lst,
					t_token *token, t_token_chunk *chunk);

#endif
