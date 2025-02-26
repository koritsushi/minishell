#include "includes/minishell.h"

void	debug_print(char **res)
{
	int i = 0;

	if (!res)
	{
		printf("NULL\n");
		return ;
	}
	while (res && res[i])
		printf("%s\n", res[i++]);
}