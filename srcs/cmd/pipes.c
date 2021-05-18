#include "minishell.h"

static void	child_magic_2(t_shell *sh, t_cmd_line *current_cmd,
int (*arr[8])(t_shell *sh, void *b), t_pipe *p)
{
	p->pid2 = fork();
	if (p->pid2)
		return ;
	if (p->change_pipe < 0)
		dup2(p->fd1[0], STDIN_FILENO);
	else
		dup2(p->fd2[0], STDIN_FILENO);
	if (current_cmd->redir)
	{
		dup2(current_cmd->redir->fd_o, STDOUT_FILENO);
		close(current_cmd->redir->fd_o);
	}
	magic_pipe_pid(sh, current_cmd, arr, *p);
}

static void	child_magic_1_v_normy(t_cmd_line *current_cmd, t_pipe *p)
{
	if (!current_cmd->redir)
		dup2(p->fd2[0], STDIN_FILENO);
	else if (current_cmd->redir->fd_i < 0)
		dup2(p->fd2[0], STDIN_FILENO);
	if (!current_cmd->redir)
		dup2(p->fd1[1], STDOUT_FILENO);
	else if (current_cmd->redir->fd_o < 0)
		dup2(p->fd1[1], STDOUT_FILENO);
}

static void	child_magic_1(t_shell *sh, t_cmd_line *current_cmd,
int (*arr[8])(t_shell *sh, void *b), t_pipe *p)
{
	p->pid1 = fork();
	if (p->pid1)
		return ;
	if (!p->change_pipe)
	{
		if (!current_cmd->redir)
			dup2(p->fd1[1], STDOUT_FILENO);
		else if (current_cmd->redir->fd_o < 0)
			dup2(p->fd1[1], STDOUT_FILENO);
	}
	else if (p->change_pipe < 0)
	{
		if (!current_cmd->redir)
			dup2(p->fd1[0], STDIN_FILENO);
		else if (current_cmd->redir->fd_i < 0)
			dup2(p->fd1[0], STDIN_FILENO);
		if (!current_cmd->redir)
			dup2(p->fd2[1], STDOUT_FILENO);
		else if (current_cmd->redir->fd_o < 0)
			dup2(p->fd2[1], STDOUT_FILENO);
	}
	else
		child_magic_1_v_normy(current_cmd, p);
	magic_pipe_pid(sh, current_cmd, arr, *p);
}

static void	normy_power(t_pipe *p, t_cmd_line *current_cmd)
{
	if (p->change_pipe > 0)
		ft_close_pipe(p->fd2);
	else
		ft_close_pipe(p->fd1);
	if (current_cmd->redir)
		if (current_cmd->redir->fd_o)
			close(current_cmd->redir->fd_o);
}

void	magic_pipe(t_shell *sh, t_list **cmd_list,
int (*arr[8])(t_shell *sh, void *b))
{
	t_pipe		p;
	t_cmd_line	*current_cmd;

	current_cmd = (*cmd_list)->content;
	p.change_pipe = 0;
	while (current_cmd->redir_pipe)
	{
		current_cmd = (*cmd_list)->content;
		pipe_choice(&p, current_cmd);
		child_magic_1(sh, current_cmd, arr, &p);
		if (current_cmd->redir)
		{
			dup2(sh->fd_sav[0], STDIN_FILENO);
			dup2(sh->fd_sav[1], STDOUT_FILENO);
		}
		magic_pipe_loop(&p, &current_cmd, &cmd_list);
	}
	child_magic_2(sh, current_cmd, arr, &p);
	normy_power(&p, current_cmd);
	waitpid(p.pid2, &p.wstatus, 0);
	*cmd_list = (*cmd_list)->next;
	sh->exit = WEXITSTATUS(p.wstatus);
}
