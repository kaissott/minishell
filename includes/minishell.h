/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 02:04:26 by ludebion          #+#    #+#             */
/*   Updated: 2025/07/23 22:42:11 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "exec/exec.h"
# include "exec/exec_utils.h"
# include "exec/builtins.h"
# include "parsing/expansion.h"
# include "parsing/parse.h"
# include "parsing/tokenisation.h"
# include "parsing/utils/debug_utils.h"
# include "parsing/utils/lst_utils.h"
# include "parsing/utils/utils.h"
# include "parsing/word_splitting.h"
# include "structures.h"
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
