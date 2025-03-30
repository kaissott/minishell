/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:45:19 by karamire          #+#    #+#             */
/*   Updated: 2025/03/30 21:52:40 by karamire         ###   ########.fr       */
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
typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}					t_env;

void				lstadd_back(t_env **lst, t_env *new);
t_env				*lstnew(char *content);
int					mini_echo(t_cmd *echo);
int					pwd_parsing(t_cmd *cmd);
t_env				*env_build(char **env);
int					env_print(t_env *env);
int					export_parsing(t_cmd *cmd, t_env *env);

#endif
