#include "includes/minishell.h"

void	debug_print(char **res)
{
	int i = 0;

	while (res[i])
		printf("%s\n", res[i++]);
}