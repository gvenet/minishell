#include <minishell.h>

static void	display_tool_redir(t_cmd_line *cmd)
{
	if (cmd->redir)
	{
		if (cmd->redir->fd_i != -1)
			printf("\033[33;01minput(id = %d, fd = %d, flag = %s)\033[00m / ", \
			cmd->redir->id_i, cmd->redir->fd_i, cmd->redir->name_i);
		if (cmd->redir->fd_o != -1)
			printf("\033[33;01moutput(id = %d, fd = %d, flag = %s)\033[00m / ", \
			cmd->redir->id_o, cmd->redir->fd_o, cmd->redir->name_o);
		if (cmd->redir->fd_n != -1)
			printf("\033[33;01merr_red(id = %d, fd = %d, flag = %s)\033[00m / ", \
			cmd->redir->id_n, cmd->redir->fd_n, cmd->redir->name_n);
	}
}

void	display_lst_cmd_line(t_shell *sh)
{
	t_cmd_line	*cmd;
	t_list		*l;
	int			i;
	int			n;

	n = 1;
	l = sh->cmd;
	while (l)
	{
		i = -1;
		cmd = l->content;
		printf("\033[33;01mcontent n%d\033[00m / ", n);
		display_tool_redir(cmd);
		if (cmd->redir_pipe)
			printf("\033[33;01mredir_pipe ON\033[00m / ");
		if (cmd->option_echo)
			printf("\033[33;01moption_echo ON\033[00m / ");
		printf("\033[33;01mcmd = %d\033[00m / ", cmd->cmd);
		while (cmd->args[++i])
			printf("\033[33;01m|%s| \033[00m", cmd->args[i]);
		printf("\n");
		n++;
		l = l->next;
	}	
}
