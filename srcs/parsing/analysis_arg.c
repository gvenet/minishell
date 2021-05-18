#include <minishell.h>

static int	analysis_bckslch(char **buf, int ret)
{
	if ((*buf)[1] == '"' || (*buf)[1] == '$' || (*buf)[1] == '\\')
	{
		*buf += 2;
		ret++;
	}
	return (ret);
}

static int	analysis_dquot(t_shell *sh, char **buf, int ret)
{
	if (**buf == 0)
		return (E_FAIL);
	if (**buf == '\\')
		ret = analysis_bckslch(buf, ret);
	else if (**buf == '$' && ft_isdigit((*buf)[1]))
		*buf += 2;
	else if (**buf == '$' && (*buf)[1] == '?')
	{
		ret += (int)ft_intlen(sh->exit);
		*buf += 2;
	}
	else if (**buf == '$' && (*buf)[1] && !is_sep((*buf)[1]) \
	&& (*buf)[1] != ' ' && !is_quot((*buf)[1]))
		analysis_env(sh, buf, &ret);
	else
	{
		(*buf)++;
		ret++;
	}
	return (ret);
}

static int	analysis_quot_selector(t_shell *sh, char **buf, int ret)
{
	if (**buf == '\'')
	{
		while (*++(*buf) != '\'')
		{
			if (**buf == 0)
				return (E_FAIL);
			ret++;
		}
		(*buf)++;
	}
	else if (**buf == '"')
	{
		(*buf)++;
		while (**buf != '"')
		{
			if (**buf == 0)
				return (E_FAIL);
			ret = analysis_dquot(sh, buf, ret);
		}
		(*buf)++;
	}
	return (ret);
}

static int	analysis_without_quot(t_shell *sh, char **buf, int ret)
{
	sh->redir_id = is_redir(sh, buf);
	if (sh->redir_id == E_FAIL)
		return (E_FAIL);
	else if (sh->redir_id != E_NO_MATCH)
	{
		if (analysis_redir(sh, buf, sh->redir_id) == E_FAIL)
			return (E_FAIL);
	}
	else if (is_bckslash(buf) == E_FAIL)
		return (E_FAIL);
	else if (is_tild(buf, ret))
		ret += analysis_tild(sh, buf, ret);
	else if (**buf == '$' && ft_isdigit((*buf)[1]))
		*buf += 2;
	else if (**buf == '$' && (*buf)[1] == '?')
		ret += exit_status_len(sh, buf, ret);
	else if (is_env(buf))
	{
		if (analysis_env(sh, buf, &ret) == E_FAIL)
			return (E_FAIL);
	}
	else
		ret = next_char_ana(sh, buf, ret);
	return (ret);
}

int	analysis_arg(t_shell *sh, char **buf)
{
	int		ret;
	char	*b_ptr;

	ret = 0;
	b_ptr = *buf;
	while (**buf && **buf != ' ' && !is_sep(**buf))
	{
		if (is_quot(**buf))
		{
			ret = analysis_quot_selector(sh, buf, ret);
		}
		else
		{
			ret = analysis_without_quot(sh, buf, ret);
			if (ret == E_FAIL)
				return (E_FAIL);
		}
		if (**buf == '>' || **buf == '<' )
			break ;
	}
	if (sh->redir_process_engaged == E_FALSE && \
	sh->getenv_process_engaged == E_FALSE)
		*buf = b_ptr;
	return (ret);
}
