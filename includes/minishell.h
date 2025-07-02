#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include "../libft/libft.h"
# include "structures.h"
# include "parsing/expansion.h"
# include "parsing/parse.h"
# include "parsing/tokenisation.h"
# include "parsing/word_splitting.h"
# include "parsing/utils/lst_utils.h"
# include "parsing/utils/utils.h"
# include "exec/main.h"
# include "exec/error.h"


#endif
