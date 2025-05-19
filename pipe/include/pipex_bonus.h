/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 05:24:53 by kaissramire       #+#    #+#             */
/*   Updated: 2025/03/31 09:19:32 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../Libft/GNL/get_next_line.h"
# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

char	**ft_split_slash(char const *s, char c);
int		heredoc(char *infile, char *limiter);
char	*path_finding(char **env);
char	*cmd_path(char *cmd, char *linktopath);
int		strrchr_slash(const char *s, int c);
void	error_exec_b(char **cmdtab, char *cmd);
char	*free_tab(char **tab, char **path);
int		check_args(int ac, char **av);
void	close_fd(int prev, int outfile, int if_hd);
int		open_input(char **av, int *i, int *if_hd);
int		open_file(char *file, int num);
int		do_cmd(char *cmd, char **env);
void	access_out_check(char *out, int prev_fd, int outfile, int if_hd);
void	close_dup_failed(int fd1, int fd2, int i);
void	error_exit(char *str, int exitnbr, int fd);

#endif
