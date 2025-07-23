/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:49:57 by karamire          #+#    #+#             */
/*   Updated: 2025/07/23 10:04:02 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

void	execve_err(t_shell *main, char **env, char *path, char *cmd);
void	init_simple_cmd(t_shell *main);
void	wait_child(pid_t last, t_shell *main);
void	ultimate_path_check(t_shell *main, char **cmd);

char	**ft_split_slash(char const *s, char c);
char	**env_to_tab(t_shell *main);

int		do_cmd(t_shell *main, char **cmd, char **env);
int		pipe_exec(t_shell *main);
int		check_current_dir_exec(t_shell *main, char **cmd);
int		strrchr_slash(const char *s, int c);
int		file_dup(t_shell *main, int fd_in, int fd_out);

char	*env_path_finding(t_shell *main, char **env);
char	*cmd_path(char **cmd, char *linktopath);
char	*get_path(t_shell *main, char *env_path, char **env);
char	*path_finding(char **env);

pid_t	dup_process_child(t_shell *main, t_exec *node, int prev_fd, int pipefd);
void	exit_exec_cmd(t_shell *main);

#endif
