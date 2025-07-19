/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:11:50 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/19 21:12:28 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../minishell.h"
# include "../structures.h"

t_parse_error	expansion(t_main *shell);
bool			is_dollar_alone(t_token_chunk *chunk, size_t i, size_t len,
					t_token_chunk *next);
t_expand		*extract_expand_var(char *var, ssize_t *i);
t_parse_error	replace_chunk_value(t_main *shell, t_expand **expand_lst,
					t_token *token, t_token_chunk *chunk);

#endif
