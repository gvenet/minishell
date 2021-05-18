#include "minishell.h"

static void	init_tab_funct(int (*arr[8])(t_shell *sh, void *b))
{
	arr[E_NO_MATCH] = ft_nomatch;
	arr[E_ECHO] = ft_echo;
	arr[E_CD] = ft_cd;
	arr[E_PWD] = ft_pwd;
	arr[E_EXPORT] = ft_export;
	arr[E_UNSET] = ft_unset;
	arr[E_ENV] = ft_env;
	arr[E_EXIT] = ft_exit;
}

int	exec_cmd(t_shell *sh)
{
	int			value;
	t_cmd_line	*current_cmd;
	t_list		*cmd_list;
	int			(*arr[8])(t_shell *sh, void *b);

	cmd_list = sh->cmd;
	value = -2;
	init_tab_funct(arr);
	while (cmd_list)
	{
		current_cmd = cmd_list->content;
		if (current_cmd->redir || current_cmd->redir_pipe)
		{
			if (current_cmd->redir_pipe)
				magic_pipe(sh, &cmd_list, arr);
			else if (current_cmd->redir)
				redirections(sh, &cmd_list, arr);
			continue ;
		}
		value = (*arr[current_cmd->cmd])(sh, current_cmd);
		cmd_list = cmd_list->next;
	}
	clear_lst_cmd(&sh->cmd);
	return (value);
}
