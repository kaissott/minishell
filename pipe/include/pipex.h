/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 05:24:53 by kaissramire       #+#    #+#             */
/*   Updated: 2025/04/01 13:00:43 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// error.c

int		check_args(int ac);
void	error_exec(char **cmdtab, char *cmd);
char	*free_tab(char **tab, char **path);
void	close_dup_failed(int fd1, int fd2, int i);
void	error_exit(char *str, int exitnbr, int fd);

// ft_split_slash.c

char	**ft_split_slash(char const *s, char c);

// main.c

pid_t	child_process(char *cmd, char **env, int prev_fd);
pid_t	last_child(char *last, int prev_fd, int outfile, char **env);
void	wait_child(pid_t last);

// open.c

int		open_input(char **av, int *i);
int		open_file(char *file, int num);

// pipex_utils.c

char	*path_finding(char **env);
char	*cmd_path(char *cmd, char *linktopath);
int		do_cmd(char *cmd, char **env);
void	close_fd(int prev_fd, int outfile);
void	access_out_check(char *out, int prev_fd, int outfile);

// strrchr_slash.c

int		strrchr_slash(const char *s, int c);

#endif
