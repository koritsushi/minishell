#include "includes/minishell.h"

void	free_chr_ptr(void **ptr)
{
	int i;
	
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}
