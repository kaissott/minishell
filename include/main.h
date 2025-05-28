/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:19:49 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/28 21:28:31 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../Libft/libft.h"
# include "builtins.h"
# include "error.h"
# include "exec.h"
# include "structures.h"
# include <fcntl.h> // pour open()
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

char	**ft_split_slash(char const *s, char c);
void	free_tabs(char **tab1, char **tab2);
void	fork_error(t_main *main, char *error);
void	free_files(t_main *main);
void	init_simple_cmd(t_main *main);
int		get_outfile_simple_cmd(t_main *main);
int		check_env_available(char **env, t_main *main);
void	env_build(char **env, t_main *main);
int		free_env(t_env *env);
bool	exec_cmd(t_main *main, int fd);
char	**env_to_tab(t_main *main);
void	file_dup(int fd_in, int fd_out);
int		get_infile_simple_cmd(t_main *main);

#endif
