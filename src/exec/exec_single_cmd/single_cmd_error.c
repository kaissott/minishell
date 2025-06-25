#include "../../../includes/minishell.h"

void	output_fd_error_one(t_main *main, char *error, int fd_in)
{
	// free_tabs(main->mainenv, NULL);a!
	// free_files(main);
	if (fd_in > 0)
		close(fd_in);
	printf(error);
}
void	output_fd_error(t_main *main, char *error)
{
	// free_tabs(main->mainenv, NULL);a!
	// free_files(main);
	printf(error);
}
void	fork_error(t_main *main, char *error)
{
	int	i;

	printf(error);
	// free_tabs(main->mainenv, NULL);a!
	// free_files(main);
}
