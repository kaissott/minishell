/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:45:19 by karamire          #+#    #+#             */
/*   Updated: 2025/05/13 00:31:17 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../Libft/libft.h"
# include "error.h"
# include "struct.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	lstadd_back(t_env **lst, t_env *new);
t_env	*lstnew(char *content);
t_env	*env_build(char **env);
int		env_print(t_env *env);
int		mini_exit(char *line, t_main *main);
int		numeric_argument_error(char *error, char **args);
int		pwd(void);
void	print_echo_with_flag(char **tab);
int		mini_echo(char *line);
int		mini_cd(char *line, t_main *main);
int		free_env(t_env *env);

#endif
