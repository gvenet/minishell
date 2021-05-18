#include <minishell.h>

void	clear_lst_arg(t_list **lst)
{
	t_list	*tmp;
	char	*s;

	while (*lst)
	{
		tmp = (*lst)->next;
		if (*lst)
		{
			s = (*lst)->content;
			free(s);
			s = NULL;
			free(*lst);
		}
		*lst = tmp;
	}
	*lst = NULL;
}
