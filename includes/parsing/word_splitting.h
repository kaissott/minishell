/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:12:06 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/19 21:12:07 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_SPLITTING_H
# define WORD_SPLITTING_H

# include "../minishell.h"
# include "../structures.h"

t_parse_error	word_splitting(t_main *shell);
bool			chunk_contains_ifs_chars(char *str);
bool			token_contains_ifs_chunks(t_token *token);
t_parse_error	keep_chunk(t_token *token, t_token_chunk *chunk);
t_parse_error	handle_first_word(t_token **new_tokens, t_token_chunk *chunk,
					char *word);
void			replace_split_token(t_token **tokens, t_token *new_tokens,
					t_token *token);

#endif
