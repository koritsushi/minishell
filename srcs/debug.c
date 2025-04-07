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

void	debug_print_lst(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	/*debug*/printf("\033[90m_____export_id definition:_____\033[0m\n");
	/*debug*/printf("\033[90m0:[0]env_list && [0]export_list\033[0m\n");
	/*debug*/printf("\033[90m1:[0]env_list && [1]export_list\033[0m\n");
	/*debug*/printf("\033[90m2:[1]env_list && [1]export_list\033[0m\n");
	/*debug*/printf("\033[103m_____vars_list:_____\033[0m\n");
	while (tmp != NULL)
	{
		/*debug*/printf("%s:\033[93m%s\033[0m. export_id[\033[93m%d\033[0m]\n", (char*)tmp->env, (char*)tmp->content, tmp->exported);
		tmp = tmp->next;
	}
	/*debug*/printf("\033[90m_________end_________\033[0m\n");
}
