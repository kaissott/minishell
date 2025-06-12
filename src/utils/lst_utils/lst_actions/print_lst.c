#include "../../../../includes/minishell.h"

void	print_lst(t_exec *lst, char *msg)
{
	size_t	i;
	size_t	j;
	ssize_t	read_ret;

	char buf[31]; // 30 + 1 pour la null-termination
	i = 1;
	printf("\n%s\n", msg);
	if (!lst)
	{
		printf("The list is empty\n");
		return ;
	}
	while (lst)
	{
		printf("Node [%zu]\n", i++);
		if (lst->cmd)
		{
			for (j = 0; lst->cmd[j]; j++)
				printf("cmd[%zu]: [%s]\n", j, lst->cmd[j]);
		}
		printf("infile fd : [%d] type : [%d]\n", lst->infile.fd,
			lst->infile.type);
		if (lst->infile.fd > 0)
		{
			read_ret = read(lst->infile.fd, buf, 30);
			if (read_ret > 0)
			{
				buf[read_ret] = '\0';
				printf("read infile fd : %s\n", buf);
			}
			else
				perror("read infile");
		}
		printf("outfile fd : [%d] type : [%d]\n", lst->outfile.fd,
			lst->outfile.type);
		if (lst->outfile.fd)
		{
			write(lst->outfile.fd, buf, 30);
			printf("buf infile : %s\n", buf);
		}
		lst = lst->next;
	}
}
