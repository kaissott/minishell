/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:45:19 by karamire          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:46 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../Libft/libft.h"
# include "error.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	char			*arg;
	char			*fd_in;
	char			*fd_out;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_p
{
	char			*arg;
	int				type;
	int				file_in;
	int				file_out;
	struct s_p		*next;
}					t_p;

typedef struct s_cmd
{
	char			*cmd;
	char			*flag;
	char			*args;
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
int					pwd_parsing(t_cmd *cmd);
t_env				*env_build(char **env);
int					env_print(t_env *env);
int					export_parsing(t_cmd *cmd, t_env *env);
int					mini_exit(char *line);
int					numeric_argument_error(char *error, char **args);
int					pwd(void);
void				print_echo_with_flag(char **tab);
int					mini_echo(char *line);

#endif
