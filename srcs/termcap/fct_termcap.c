#include "minishell.h"

void	del_termcap(char **term, t_shell *sh)
{
	int	len;

	len = ft_strlen(*term);
	*term = realloc_maison(*term, len);
	if (sh->t->position)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		sh->t->position--;
	}
}

void	tab_termcap(char **term, t_shell *sh)
{
	int	len;

	write(STDOUT_FILENO, "    ", 4);
	len = ft_strlen(*term);
	*term = realloc_maison(*term, len + 6);
	(*term)[len] = ' ';
	(*term)[len + 1] = ' ';
	(*term)[len + 2] = ' ';
	(*term)[len + 3] = ' ';
	sh->t->position += 4;
}
