/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:11:42 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 08:34:25 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_UTILS_H
# define DEBUG_UTILS_H

# include "minishell.h"
# include "structures.h"

void			print_token_lst(t_token *lst, char *msg);
void			print_chunk_lst(t_token_chunk *lst, char *msg);
void			print_exec_lst(t_exec *lst, char *msg);

#endif
