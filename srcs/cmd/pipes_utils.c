#include "minishell.h"

void	ft_close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static void	pipe_redir(t_cmd_line *current_cmd)
{
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
}

void	pipe_choice(t_pipe *p, t_cmd_line *current_cmd)
{
	if (p->change_pipe < 0)
	{
		if (pipe(p->fd2) == -1)
		{
			write(STDERR_FILENO, "Could not open the pipe\n", \
			ft_strlen("Could not open the pipe\n"));
			return ;
		}
	}
	else
	{
		if (pipe(p->fd1) == -1)
		{
			write(STDERR_FILENO, "Could not open the pipe\n", \
			ft_strlen("Could not open the pipe\n"));
			return ;
		}
	}
	if (current_cmd->redir)
		pipe_redir(current_cmd);
}

void	magic_pipe_pid(t_shell *sh, t_cmd_line	*current_cmd,
int (*arr[8])(t_shell *sh, void *b), t_pipe p)
{
	if (p.change_pipe < 0)
		ft_close_pipe(p.fd1);
	else
		ft_close_pipe(p.fd2);
	(*arr[current_cmd->cmd])(sh, current_cmd);
	exit (sh->exit);
}

void	magic_pipe_loop(t_pipe *p, t_cmd_line **current_cmd, t_list ***cmd_list)
{
	if (p->change_pipe > 0)
		ft_close_pipe(p->fd2);
	else if (p->change_pipe < 0)
		ft_close_pipe(p->fd1);
	if (!p->change_pipe)
		p->change_pipe++;
	p->change_pipe *= -1;
	waitpid(p->pid1, NULL, 0);
	**cmd_list = (**cmd_list)->next;
	*current_cmd = (**cmd_list)->content;
}
