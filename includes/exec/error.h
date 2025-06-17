#ifndef ERROR_H
# define ERROR_H

# include "structures.h"

void	free_and_exit_error(t_main *main, char *error, int err_number);
int		set_return_err_code(t_main *main, char *error, int err_number);

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

#endif
