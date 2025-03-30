/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:45:19 by karamire          #+#    #+#             */
/*   Updated: 2025/03/30 18:06:05 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <unistd.h>

typedef struct s_cmd
{
	char			*cmd;
	char			*flag;
	char			**args;
	int				input;
	int				output;
	struct s_cmd	*next;
}					t_cmd;

void				lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd				*lstnew(char *content);
int					mini_echo(t_cmd *echo);
int					pwd_parsing(t_cmd *cmd);

#endif
