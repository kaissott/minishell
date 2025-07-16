#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "exec/error.h"
# include "exec/exec.h"
# include "exec/main.h"
# include "parsing/expansion.h"
# include "parsing/parse.h"
# include "parsing/tokenisation.h"
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

extern volatile sig_atomic_t	g_sig_mode;
void							init_sigaction(int mode);

#endif
