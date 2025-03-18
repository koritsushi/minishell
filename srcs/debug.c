#include "includes/minishell.h"

void	debug_print(char **res)
{
	int	i = 0;

	if (!res)
	{
		printf("NULL\n");
		return ;
	}
	while (res && res[i])
		printf("%s\n", res[i++]);
}

void	debug_print_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		/*debug*/printf("v:\033[93m%s\033[0m. export_id[\033[93m%d\033[0m]\n", (char*)tmp->content, tmp->export_id);
		tmp = tmp->next;
	}
}
