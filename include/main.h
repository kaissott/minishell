/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:19:49 by kaissramire       #+#    #+#             */
/*   Updated: 2025/06/10 19:28:15 by karamire         ###   ########.fr       */
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
bool	exec_cmd(t_main *main, char **cmd, bool simple);
char	**env_to_tab(t_main *main);
void	file_dup(int fd_in, int fd_out);
int		get_infile_simple_cmd(t_main *main);
char	*free_tab_pipe(char **tab, char **path);
// char	**ft_split_slash(char const *s, char c);
int		heredoc(char *infile, char *limiter);
char	*path_finding(char **env);
char	*cmd_path(char **cmd, char *linktopath);
int		strrchr_slash(const char *s, int c);
void	error_exec_b(char **cmdtab, char *cmd);
char	*free_tab(char **tab, char **path);
int		check_args(int ac, char **av);
void	close_fd(int prev, int outfile, int if_hd);
int		open_input(char **av, int *i, int *if_hd);
int		open_file(char *file, int num);
int		do_cmd(t_main *main, char **cmd, char **env);
void	access_out_check(char *out, int prev_fd, int outfile, int if_hd);
void	close_dup_failed(int fd1, int fd2, int i);
void	error_exit(char *str, int exitnbr, int fd);
int		create_node(t_main *main, char *line);
int		pipe_exec(t_main *main);
int		free_struct(t_main *main);
void	free_node(t_main *main);

#endif
