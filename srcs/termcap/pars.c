#include "minishell.h"

int	g_lobal = 0;

void	fc_cc(int a)
{
	g_lobal++;
	write(1, "\n", 1);
	ms_prompt();
	(void)a;
}

static int	termcap_normal_key(t_shell *sh, int read, char **term)
{
	int	len;

	if (read == 10)
		return (0);
	else if (read == 127)
		del_termcap(term, sh);
	else if (read == 9)
		tab_termcap(term, sh);
	else if (read == 27)
		return (1);
	else if (read < 127 && read > 30)
	{
		write(STDOUT_FILENO, &read, sizeof(read));
		len = ft_strlen(*term);
		*term = realloc_maison(*term, len + 2);
		(*term)[len] = read;
		sh->t->position++;
	}
	return (1);
}

static int	signaux_home_made(t_shell *sh, int read, char **term)
{
	if (read == 3)
		return (E_FAIL);
	else if (read == 4)
	{
		if (!ft_strlen(*term))
		{
			write(STDIN_FILENO, "\n", 1);
			free_shell(sh, 0);
		}
	}
	return (1);
	(void)term;
}

/*
ctrl + c = 3
ctrl + d = 4
ctrl + \ = 28
fleche haut: 4283163
fleche bas: 4348699
*/

static int	termcap_pars_algo(t_shell *sh, char **term)
{
	int		ret;
	int		reading;

	reading = 0;
	ret = read(STDIN_FILENO, &reading, sizeof(reading));
	if (g_lobal)
	{
		del_fct(term);
		*term = (char *)ft_memalloc(1);
		sh->t->position = 0;
		g_lobal = 0;
	}
	if (ret == 4)
		return (E_FAIL);
	else if (reading == 4283163 || reading == 4348699)
	{
		sh->hist.current_history = cmd_history(sh, reading, term);
		sh->t->position = ft_strlen(*term);
	}
	else if (reading == 3 || reading == 4 || reading == 28)
		ret = signaux_home_made(sh, reading, term);
	else if (reading >= 9 && reading < 128)
		ret = termcap_normal_key(sh, (char)reading, term);
	return (ret);
}

char	*termcap_pars(t_shell *sh)
{
	char	*term;
	int		ret;

	sh->hist.history_len = ft_strlen_2d(sh->hist.history);
	sh->hist.current_history = sh->hist.history_len;
	term = (char *)ft_memalloc(1);
	if (term == NULL)
		return (NULL);
	ret = 1;
	sh->t->position = 0;
	while (ret > 0)
	{
		ret = termcap_pars_algo(sh, &term);
	}
	if (!term[0] || ret == E_FAIL)
		del_fct(&term);
	if (sh->hist.history_len < HISTSIZE && term)
		sh->hist.history[sh->hist.history_len] = ft_strdup(term);
	return (term);
}
