#include "minishell.h"

static void	down_history(t_shell *sh, char **term)
{
	tputs(tgetstr("dl", NULL), 1, ft_putchar);
	write(STDIN_FILENO, "\r", 1);
	ms_prompt();
	if (sh->hist.current_history < sh->hist.history_len)
		sh->hist.current_history++;
	if (sh->hist.history[sh->hist.current_history])
	{
		write(STDOUT_FILENO, sh->hist.history[sh->hist.current_history], \
		strlen(sh->hist.history[sh->hist.current_history]));
		del_fct(term);
		*term = ft_strdup(sh->hist.history[sh->hist.current_history]);
	}
	else if (sh->hist.current_history == sh->hist.history_len)
	{
		del_fct(term);
		*term = ft_strdup("");
	}
}

static void	up_history(t_shell *sh, char **term)
{
	tputs(tgetstr("dl", NULL), 1, ft_putchar);
	write(STDIN_FILENO, "\r", 1);
	ms_prompt();
	if (sh->hist.current_history)
		sh->hist.current_history--;
	if (sh->hist.history[sh->hist.current_history])
	{
		write(STDOUT_FILENO, sh->hist.history[sh->hist.current_history], \
		strlen(sh->hist.history[sh->hist.current_history]));
		del_fct(term);
		*term = ft_strdup(sh->hist.history[sh->hist.current_history]);
	}
}

int	cmd_history(t_shell *sh, int read, char **term)
{
	if (read == 4283163)
		up_history(sh, term);
	else if (read == 4348699)
		down_history(sh, term);
	return (sh->hist.current_history);
}
