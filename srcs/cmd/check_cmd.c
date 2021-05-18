#include "minishell.h"

static void	collect_paths(t_shell *sh, t_c_pid *child)
{
	char	**paths_tmp;
	char	**paths;
	int		i;

	i = -1;
	paths_tmp = NULL;
	while (sh->env[++i] && !paths_tmp)
	{
		if (!ft_strncmp(sh->env[i], "PATH=", ft_strlen("PATH=")))
			paths_tmp = ft_split(sh->env[i] + ft_strlen("PATH="), ':');
	}
	if (!paths_tmp)
		paths = NULL;
	else
	{
		i = -1;
		while (paths_tmp[++i])
			;
		paths = (char **)malloc(sizeof(char *) * (i + 1));
		paths[i] = NULL;
		while (i--)
			paths[i] = ft_strjoin(paths_tmp[i], "/");
		paths_tmp = ft_strdel_2d(paths_tmp);
	}
	child->env_path = paths;
}

static void	init_child(t_c_pid *child)
{
	child->i = -1;
	child->y = -1;
	child->fd = -1;
	child->env_path = NULL;
	child->path = NULL;
}

static void	child_process(t_shell *sh, t_cmd_line *cmd, int *err)
{
	t_c_pid	child;

	init_child(&child);
	if (!ft_memchr(cmd->args[0], '/', ft_strlen(cmd->args[0])))
		collect_paths(sh, &child);
	if (child.env_path)
	{
		child.path = child.env_path;
		while (child.path[++child.i])
			child.path[child.i] = ft_strjoin(child.path[child.i], cmd->args[0]);
		child.i++;
		while (child.fd < 0 && child.i--)
			child.fd = open(child.path[++child.y], O_RDONLY);
	}
	else
	{
		if (!child.path)
			child.path = (char **)malloc(sizeof(char *));
		child.path[++child.y] = cmd->args[0];
	}
	if (child.fd > 0)
		if (close(child.fd))
			exit(E_FAIL);
	execve(child.path[child.y], cmd->args, sh->env);
	*err = errno;
}

static void	print_msg_err(t_cmd_line *cmd)
{
	write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	write(2, ": command not found\n", \
	ft_strlen(": command not found\n"));
}

//SIG_DFL	default signal handling
int	test_cmd(t_shell *sh, t_cmd_line *cmd, int id, int err)
{
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process(sh, cmd, &err);
		if (err)
			print_msg_err(cmd);
		exit(127);
	}
	else
	{
		signal(SIGINT, &ft_c);
		signal(SIGQUIT, &ft_bs);
		wait(&err);
	}
	if (WIFEXITED(err))
	{
		err = WEXITSTATUS(err);
		if (!err)
			return (ret_exit(sh, 0, E_SUCCESS));
		else
			return (ret_exit(sh, err, err));
	}
	return (-1);
}
