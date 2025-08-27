/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:04:26 by ludebion          #+#    #+#             */
/*   Updated: 2025/08/27 08:29:45 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define INTERACTIVE 0
# define CHILD 1
# define HERE_DOC 2
# define SIG 130

# include "../libft/libft.h"
# include "exec/builtins.h"
# include "exec/exec.h"
# include "exec/exec_utils.h"
# include "parsing/expansion.h"
# include "parsing/parse.h"
# include "parsing/parsing_utils/debug_utils.h"
# include "parsing/parsing_utils/lst_utils.h"
# include "parsing/parsing_utils/parsing_utils.h"
# include "parsing/tokenisation.h"
# include "parsing/word_splitting.h"
# include "structures.h"
# include "shell_utils.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_sig_mode;

t_shell		*init_minishell(char **env);

#endif
