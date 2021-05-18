#include "minishell.h"

void	del_fct(char **x)
{
	free(*x);
	*x = NULL;
}

void	del_fct_int(int **x)
{
	free(*x);
	*x = NULL;
}
