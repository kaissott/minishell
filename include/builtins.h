/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:45:19 by karamire          #+#    #+#             */
/*   Updated: 2025/05/28 20:10:34 by kaissramire      ###   ########.fr       */
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

// echo

void	print_echo_with_flag(char **tab);
int		mini_echo(t_main *main);

// pwd

int		pwd(t_main *main, int fd);

// env
int		env_print(t_main *main);

void	lstadd_back(t_env **lst, t_env *new);
t_env	*lstnew(char *content);
int		mini_exit(char *line, t_main *main);
int		numeric_argument_error(char *error, char **args);
int		mini_cd(char *line, t_main *main);
void	free_tab_exit(char **args);
void	free_tab(char **tab1, char **tab2);

#endif
