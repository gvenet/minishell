#include "minishell.h"

static void	child_process(t_shell *sh, t_cmd_line *current_cmd,
int (*arr[8])(t_shell *sh, void *b), int err[2])
{
	close(err[0]);
	if (current_cmd->redir->fd_i > 1)
	{
		dup2(current_cmd->redir->fd_i, STDIN_FILENO);
		close(current_cmd->redir->fd_i);
	}
	if (current_cmd->redir->fd_o > 1)
	{
		dup2(current_cmd->redir->fd_o, STDOUT_FILENO);
		close(current_cmd->redir->fd_o);
	}
	if (current_cmd->redir->fd_n > 1)
	{
		dup2(current_cmd->redir->fd_n, STDERR_FILENO);
		close(current_cmd->redir->fd_n);
	}
	(*arr[current_cmd->cmd])(sh, current_cmd);
	write(err[1], &sh->exit, sizeof(int));
	close(err[1]);
	exit (E_SUCCESS);
}

static int	close_all(t_cmd_line *current_cmd, int err[2])
{
	int			k;

	close(current_cmd->redir->fd_o);
	close(current_cmd->redir->fd_i);
	close(current_cmd->redir->fd_n);
	close(err[1]);
	read(err[0], &k, sizeof(int));
	close(err[0]);
	return (k);
}

static int	normy1(t_shell *sh, t_cmd_line *current_cmd, t_list **cmd_list)
{
	if (current_cmd->cmd == E_EXIT)
	{
		ft_exit(sh, current_cmd);
		return (1);
	}
	if (current_cmd->cmd == E_CD)
	{
		ft_cd(sh, current_cmd);
		*cmd_list = (*cmd_list)->next;
		return (1);
	}
	return (0);
}

void	redirections(t_shell *sh, t_list **cmd_list,
int (*arr[8])(t_shell *sh, void *b))
{
	int			pid;
	int			err[2];
	int			k;
	t_cmd_line	*current_cmd;

	current_cmd = (*cmd_list)->content;
	pid = normy1(sh, current_cmd, cmd_list);
	if (pid)
		return ;
	if (pipe(err) == -1)
	{
		write(STDERR_FILENO, "Could not open the pipe\n", \
		ft_strlen("Could not open the pipe\n"));
		return ;
	}
	pid = fork();
	if (pid == 0)
		child_process(sh, current_cmd, arr, err);
	k = close_all(current_cmd, err);
	waitpid(pid, NULL, 0);
	ret_exit(sh, k, 0);
	*cmd_list = (*cmd_list)->next;
}
