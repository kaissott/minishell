/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:45:19 by karamire          #+#    #+#             */
/*   Updated: 2025/05/22 16:23:13 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../Libft/libft.h"
# include "error.h"
# include "structures.h"
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
void	free_tab_exit(char **args);
void	free_tab(char **tab1, char **tab2);

#endif
