#include <minishell.h>

static	void	create_lst_arg(t_shell *sh, char **buf, int analysis_ret)
{
	char	*arg;

	arg = NULL;
	if (!sh->env_does_not_exist || (sh->env_does_not_exist && analysis_ret))
	{
		arg = fill_arg(sh, buf, arg, analysis_ret);
		ft_lstadd_back(&sh->lst_arg, ft_lstnew(arg));
		sh->lst_arg = check_echo_option(sh, sh->lst_arg);
	}
	else
	{
		while (**buf && !is_sep(**buf) && **buf != ' ')
			(*buf)++;
	}
}

static	int	analysis_and_treatment(t_shell *sh, char **buf)
{
	int		analysis_ret;

	sh->redir_process_engaged = E_FALSE;
	sh->env_does_not_exist = E_FALSE;
	sh->pars_char = E_FALSE;
	*buf = trim_ws(*buf);
	if (is_sep(**buf))
		return (E_FAIL);
	analysis_ret = analysis_arg(sh, buf);
	if (analysis_ret == E_FAIL)
		return (E_FAIL);
	if (!sh->redir_process_engaged)
		create_lst_arg(sh, buf, analysis_ret);
	*buf = trim_ws(*buf);
	return (E_SUCCESS);
}

static int	eol_fail(t_shell *sh)
{
	write(STDERR_FILENO, "syntax error\n", 13);
	clear_lst_arg(&sh->lst_arg);
	clear_lst_cmd(&sh->cmd);
	clear_sh_redir(sh);
	return (ret_exit(sh, 2, E_FAIL));
}

int	pars_line(t_shell *sh, char *buf)
{
	if (check_unique_sep_error(buf) == E_FAIL)
		return (eol_fail(sh));
	while (*buf)
	{
		sh->redir_process_engaged = E_FALSE;
		sh->getenv_process_engaged = E_FALSE;
		sh->tmp_option_echo = E_FALSE;
		while (is_sep(*buf) == 0 && *buf)
			if (analysis_and_treatment(sh, &buf) == E_FAIL)
				return (eol_fail(sh));
		if (sh->lst_arg != NULL)
			create_cmd_list(sh);
		clear_lst_arg(&sh->lst_arg);
		if (sh->cmd == NULL)
			close(sh->redir->fd_o);
		clear_sh_redir(sh);
		if (check_sep_end_line(sh->cmd, &buf) == E_FAIL)
			return (eol_fail(sh));
		exec_for_pipe(sh);
	}
	return (E_SUCCESS);
}
