/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:19:49 by karamire          #+#    #+#             */
/*   Updated: 2025/08/27 19:35:50 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include "../minishell.h"
# include "structures.h"

# define ERR_MEM "Malloc failed"
# define ERR_MANY_ARGS ": too many arguments\n"
# define ERR_INV_ID ": not a valid identifier\n"
# define ERR_CMD_NOT_FOUND ": command not found\n"
# define ERR_NUM_ARG ": numeric argument required\n"
# define ERR_CD_FILE ": No such file or directory\n"
# define ERR_CD_NAMETOOLONG ": File name too long\n"
# define ERR_CD_NOACCES ": Can't acces file"
# define ERR_GETCWD "getcwd error"
# define ERR_CHDIR "chdir error"
# define ERR_WRITE "write error"
# define ERR_CD_TOO_MANY_ARGS ": too many arguments\n"
# define ERR_FORK "Error: fork failed\n"

int		check_input(t_shell *main);
int		free_struct(t_shell *main);
void	free_node(t_shell *main);
void	free_env(t_shell *main);
void	reset_struct(char *rl, t_shell *main);
void	free_tab(char **tab);
void	exit_error_two_close(t_shell *main_struct, int *fd1, int *fd2);
void	exit_error_minishell(t_shell *main, int errcode, char *err);
void	close_node(t_shell *main);
void	close_fork(int *fd1, int *fd2, t_exec *node, t_shell *main);
void	error_fork(int *pipefd, int prevfd, t_exec *node, t_shell *main);
void	error_pipe(int prevfd, t_exec *node, t_shell *main);
void	free_and_exit_error(t_shell *main, char *tmp, char *error,
			int err_number);
int		set_return_err_code(t_shell *main, char *error, int err_number);
void	ft_close(t_shell *main, int fd, int fd2, int fd3);
void	ft_safe_close(int *fd, t_shell *main);
bool	is_a_file(int *fd, t_shell *shell);
void	ft_safe_close_node(t_exec *tmp, int *fd1, int *fd2);

#endif
