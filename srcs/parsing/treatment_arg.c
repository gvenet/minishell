#include <minishell.h>

static char	*treatment_dquote(t_shell *sh, char **buf, char *s)
{
	if (**buf == '\\')
	{
		if ((*buf)[1] == '"' || (*buf)[1] == '$' || (*buf)[1] == '\\')
			(*buf)++;
		*s++ = *(*buf)++;
	}
	else if (**buf == '$' && ft_isdigit((*buf)[1]))
		(*buf) += 2;
	else if (**buf == '$' && (*buf)[1] == '?')
		s = treatment_sh_exit(sh, buf, s);
	else if (**buf == '$' && (*buf)[1] && !is_sep((*buf)[1]) && \
	(*buf)[1] != ' ' && !is_quot((*buf)[1]))
		s = treatment_env(sh, buf, s);
	else
		*s++ = *(*buf)++;
	return (s);
}

static char	*treatment_quot_selector(t_shell *sh, char **buf, char *s)
{
	if (**buf == '\'')
	{	
		while (*++(*buf) != '\'')
			*s++ = **buf;
		(*buf)++;
	}
	else if (**buf == '"')
	{	
		(*buf)++;
		while (**buf != '"')
			s = treatment_dquote(sh, buf, s);
		(*buf)++;
	}
	return (s);
}

static char	*treat_without_quot(t_shell *sh, char **buf, char *s, int *tild_b)
{
	if (**buf == '\\')
	{
		(*buf)++;
		*s++ = *(*buf)++;
	}
	else if (is_tild(buf, *tild_b))
		s = treatment_tild(buf, s);
	else if (**buf == '$' && (*buf)[1] == '?')
		s = treatment_sh_exit(sh, buf, s);
	else if (**buf == '$' && ft_isdigit((*buf)[1]))
		(*buf) += 2;
	else if (is_env(buf))
		s = treatment_env(sh, buf, s);
	else
	{
		*tild_b = 1;
		*s++ = *(*buf)++;
	}
	return (s);
}

char	*treatment_arg(t_shell *sh, char **buf, char *s)
{
	char	*s_ptr;
	int		tild_bool;

	tild_bool = 0;
	s_ptr = s;
	while (**buf && **buf != ' ' && !is_sep(**buf) && **buf != '>' \
	&& **buf != '<')
	{
		if (is_quot(**buf))
			s = treatment_quot_selector(sh, buf, s);
		else
			s = treat_without_quot(sh, buf, s, &tild_bool);
	}
	return (s_ptr);
}
