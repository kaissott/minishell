/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaissramirez <kaissramirez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:49:57 by karamire          #+#    #+#             */
/*   Updated: 2025/07/22 20:59:32 by kaissramire      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../minishell.h"

void	execve_err(t_main *main, char **env, char *path, char *cmd);
void	init_simple_cmd(t_main *main);
void	wait_child(pid_t last, t_main *main);
void	ultimate_path_check(t_main *main, char **cmd);

char	**ft_split_slash(char const *s, char c);
char	**env_to_tab(t_main *main);

int		do_cmd(t_main *main, char **cmd, char **env);
int		pipe_exec(t_main *main);
int		check_current_dir_exec(t_main *main, char **cmd);
int		strrchr_slash(const char *s, int c);
int		file_dup(t_main *main, int fd_in, int fd_out);

char	*env_path_finding(t_main *main, char **env);
char	*cmd_path(char **cmd, char *linktopath);
char	*get_path(t_main *main, char *env_path, char **env);
char	*path_finding(char **env);

pid_t	dup_process_child(t_main *main, t_exec *node, int prev_fd, int pipefd);

#endif
