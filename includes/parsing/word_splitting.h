/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:12:06 by ludebion          #+#    #+#             */
/*   Updated: 2025/09/02 03:17:41 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_SPLITTING_H
# define WORD_SPLITTING_H

# include "minishell.h"
# include "structures.h"

# define DEFAULT_IFS " \n\t"

t_parse_error	word_splitting(t_shell *shell);
bool			begin_or_end_by_ifs(t_shell *shell, char *str, int begin);
bool			chunk_contains_ifs_chars(t_shell *shell, char *str);
bool			token_contains_ifs_chunks(t_shell *shell, t_token *token);
t_parse_error	keep_chunk(t_token *token, t_token_chunk *chunk);
t_parse_error	handle_first_word(t_token **new_tokens, char *word);
void			replace_split_token(t_token **tokens, t_token *new_tokens,
					t_token *token);

#endif
