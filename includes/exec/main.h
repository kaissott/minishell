/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:19:49 by kaissramire       #+#    #+#             */
/*   Updated: 2025/07/23 10:04:02 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../../libft/libft.h"
# include "builtins.h"
# include "error.h"
# include "structures.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int		check_input(t_shell *main);
void	free_tabs(char **tab1, char **tab2);
void	fork_error(t_shell *main, char *error);
int		check_env_available(char **env, t_shell *main);
void	env_build(char **env, t_shell *main);
bool	exec_cmd(t_shell *main, char **cmd, bool simple);
char	*free_tab_pipe(char **tab, char **path);
void	error_exec_b(char **cmdtab, char *cmd);
int		check_args(int ac, char **av);
void	close_fd(int prev, int outfile, int if_hd);
void	access_out_check(char *out, int prev_fd, int outfile);
void	close_fork_failed(int fd1, int fd2, int fd3, t_shell *main);
void	error_exit(char *str, int exitnbr, int fd);
int		free_struct(t_shell *main);
void	free_node(t_shell *main);
void	reset_struct(char *rl, t_shell *main);
int		check_input(t_shell *main);
void	free_tab_2(char **tab);
void	exit_error_two_close(t_shell *main_struct, int fd1, int fd2);
void	exit_error_minishell(t_shell *main, int errcode, char *err);
void	exit_error_one_close(t_shell *main_struct, int *fd1);
void	close_main_fds(t_shell *main);
void	close_node(t_shell *main);
void	close_fork(int fd1, int fd2, t_exec *node, t_shell *main);
void	error_fork(int *pipefd, int prevfd, t_exec *node, t_shell *main);
void	error_pipe(int prevfd, t_exec *node, t_shell *main);
void	safe_close(int fd, t_shell *main);
void	free_and_exit_error(t_shell *main, char *tmp, char *error,
			int err_number);
int		set_return_err_code(t_shell *main, char *error, int err_number);

#endif
