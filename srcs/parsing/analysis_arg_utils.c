#include <minishell.h>

int	is_tild(char **buf, int ret)
{
	if (**buf == '~' && ret == 0 && ((*buf)[1] == 0 \
	|| is_sep((*buf)[1]) || (*buf)[1] == ' ' || (*buf)[1] == '/' ))
		return (1);
	return (0);
}

int	analysis_tild(t_shell *sh, char **buf, int ret)
{
	ret += f_getenv("HOME", sh, NULL);
	(*buf)++;
	return (ret);
}

int	is_env(char **buf)
{
	if (**buf == '$' && (*buf)[1] && \
	!is_sep((*buf)[1]) && (*buf)[1] != ' ')
		return (1);
	return (0);
}

int	exit_status_len(t_shell *sh, char **buf, int ret)
{
	ret += (int)ft_intlen(sh->exit);
	(*buf) += 2;
	return (ret);
}

int	next_char_ana(t_shell *sh, char **buf, int ret)
{
	sh->pars_char = E_TRUE;
	(*buf)++;
	ret++;
	return (ret);
}
