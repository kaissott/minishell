#include "../../../includes/minishell.h"

int	strrchr_slash(const char *s, int c)
{
	int	i;

	c = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
