#include <minishell.h>

int	check_unique_sep_error(char *buf)
{
	buf = trim_ws(buf);
	if (is_sep(*buf))
		return (E_FAIL);
	return (E_SUCCESS);
}

int	check_sep_end_line(t_list *l, char **buf)
{
	char		b_ptr;
	t_cmd_line	*cmd;

	b_ptr = **buf;
	if (is_sep(**buf))
	{
		if (**buf == '|' && l)
		{
			while (l)
			{
				cmd = l->content;
				l = l->next;
			}
			cmd->redir_pipe = 1;
		}
		(*buf)++;
	}
	(*buf) = trim_ws(*buf);
	if (is_sep(**buf) || (b_ptr == '|' && **buf == 0))
		return (E_FAIL);
	return (E_SUCCESS);
}

void	exec_for_pipe(t_shell *sh)
{
	t_list		*l;

	if (!sh->cmd)
		return ;
	l = sh->cmd;
	while (l->next)
		l = l->next;
	if (!((t_cmd_line *)l->content)->redir_pipe)
		exec_cmd(sh);
}

char	*fill_arg(t_shell *sh, char **buf, char *arg, int n)
{
	arg = (char *)msh_malloc((n + 1), sizeof(char));
	arg = treatment_arg(sh, buf, arg);
	return (arg);
}
