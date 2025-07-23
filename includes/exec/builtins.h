/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:45:19 by karamire          #+#    #+#             */
/*   Updated: 2025/07/23 10:04:02 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "error.h"
# include "structures.h"

/* ===========================================================================
 * MINI_ECHO
 * ===========================================================================
 */
bool	check_echo_flag(char *tab);
bool	mini_echo(t_shell *main, char **cmd);
void	print_echo_without_flag(t_shell *main, char **tab);
void	print_echo_with_flag(t_shell *main, char **tab);

/* ===========================================================================
 * MINI_PWD
 * ===========================================================================
 */
bool	pwd(t_shell *main);

/* ===========================================================================
 * MINI_ENV
 * ===========================================================================
 */
bool	env_print(t_shell *main, char **cmd);
t_env	*lstnew_env(char *content, t_shell *main);
void	lstadd_back_env(t_env **lst, t_env *new);

/* ===========================================================================
 * MINI_CD
 * ===========================================================================
 */
bool	mini_cd(char **cmd, t_shell *main);
char	*get_directory(t_shell *main, char **tab);
char	*cd_to_last_pwd(t_shell *main);
char	*cd_to_home(t_shell *main, char *path, int i);
void	env_pwd_update(t_shell *main);
void	env_oldpwd_update(t_shell *main);

/* ===========================================================================
 * MINI_EXIT
 * ===========================================================================
 */
int		mini_exit(char **line, t_shell *main);
int		check_and_conv_exit_code(char **exit, int size, t_shell *main);
void	exit_minishell(t_shell *main, int exitcode);
void	numeric_argument_error(char **args, t_shell *main);

/* ===========================================================================
 * MINI_EXPORT
 * ===========================================================================
 */
bool	mini_export(t_shell *main, char **cmd);
bool	is_valid_identifier(const char *str);
int		check_var_exist(t_shell *main, char *var);
void	print_export_env(t_shell *main);
void	export_new_var(t_shell *main, char *var);
void	replace_var(t_shell *main, char *var, t_env *env);

/* ===========================================================================
 * MINI_UNSET
 * ===========================================================================
 */
bool	mini_unset(t_shell *main, char **cmd);
void	delete_env_node(t_env **env, char *var);

#endif
