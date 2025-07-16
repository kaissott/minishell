/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:45:19 by karamire          #+#    #+#             */
/*   Updated: 2025/07/16 21:03:17 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "error.h"
# include "structures.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// echo

void	print_echo_with_flag(t_main *main, char **tab);
bool	mini_echo(t_main *main, char **cmd);

// pwd

bool	pwd(t_main *main);

// env
bool	env_print(t_main *main, char **cmd);

void	lstadd_back(t_env **lst, t_env *new);
t_env	*lstnew(char *content);
int		mini_exit(char **line, t_main *main);
int		numeric_argument_error(char *error, char **args);
bool	mini_cd(char *line, t_main *main);
void	free_tab_exit(char **args);
// void	free_tab(char **tab1, char **tab2);
bool	mini_export(t_main *main, char **cmd);
bool	mini_unset(t_main *main, char **cmd);

#endif
