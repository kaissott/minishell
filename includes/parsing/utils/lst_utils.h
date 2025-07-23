/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:11:45 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 10:04:02 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_UTILS_H
# define LST_UTILS_H

# include "minishell.h"
# include "structures.h"

void			chunk_lst_add_back(t_token_chunk **chunk_lst,
					t_token_chunk *new);
t_parse_error	create_and_add_chunk(t_token_chunk **chunk_lst, char *cmd,
					ssize_t len, char quote);
t_parse_error	create_and_add_splitted_chunk(t_token_chunk **chunk_lst,
					char *value);
void			chunk_lst_delone(t_token_chunk **chunk_lst,
					t_token_chunk *node_to_delete);
t_parse_error	cat_chunks(t_token *token);

t_exec			*create_exec_cmd(void);
void			exec_lst_add_back(t_exec **exec_lst, t_exec *new);
void			exec_lst_delone(t_exec *lst, t_exec *node_to_delete);

void			print_expand_lst(t_expand *lst, char *msg);
t_expand		*create_expand(t_expand_type type, char *value);
void			expand_lst_add_back(t_expand **lst, t_expand *new);
void			expand_lst_delone(t_expand **expand_lst,
					t_expand *node_to_delete);

t_token			*token_lst_last(t_token *lst);
void			token_lst_delone(t_token **token_lst, t_token *node_to_delete);
void			token_lst_add_back(t_token **token_lst, t_token *new);
t_parse_error	token_lst_add_operator_node(t_token **token_lst, char *cmd,
					ssize_t len, t_token_type token_type);
t_parse_error	token_lst_add_chunks(t_shell *shell, t_token *new_token);

t_parse_error	create_first_token(t_token **new_tokens, t_token_chunk *chunk);
t_parse_error	create_new_token_with_word(t_token **new_tokens, char *word);

void			free_exec(t_exec *exec);
void			free_exec_lst(t_exec **exec_lst);
void			free_expand_lst(t_expand **expand_lst);
void			free_token(t_token *token);
void			free_token_lst(t_token **token_lst);

#endif
