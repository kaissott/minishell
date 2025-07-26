/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludebion <ludebion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:04:26 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/26 20:14:23 by ludebion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define INTERACTIVE 0
# define CHILD 1
# define HERE_DOC 2
# define SIG 130

# include "../libft/libft.h"
# include "exec/exec.h"
# include "exec/exec_utils.h"
# include "exec/builtins.h"
# include "parsing/expansion.h"
# include "parsing/parse.h"
# include "parsing/tokenisation.h"
# include "parsing/utils/debug_utils.h"
# include "parsing/utils/lst_utils.h"
# include "parsing/utils/parse_utils.h"
# include "parsing/word_splitting.h"
# include "structures.h"
# include "utils.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <termios.h>

extern volatile sig_atomic_t	g_sig_mode;

#endif
