#include <minishell.h>

static int	cmp_cmd(char *cmd)
{
	int	cmp;

	cmd = ft_str_tolower(cmd);
	cmp = ft_strncmp(cmd, "echo", 7);
	if (!cmp)
		return (E_ECHO);
	cmp = ft_strncmp(cmd, "cd", 7);
	if (!cmp)
		return (E_CD);
	cmp = ft_strncmp(cmd, "pwd", 7);
	if (!cmp)
		return (E_PWD);
	cmp = ft_strncmp(cmd, "export", 7);
	if (!cmp)
		return (E_EXPORT);
	cmp = ft_strncmp(cmd, "unset", 7);
	if (!cmp)
		return (E_UNSET);
	cmp = ft_strncmp(cmd, "env", 7);
	if (!cmp)
		return (E_ENV);
	cmp = ft_strncmp(cmd, "exit", 7);
	if (!cmp)
		return (E_EXIT);
	return (E_NO_MATCH);
}

static void	get_cmd_line(t_cmd_line *current_cmd, char **args)
{
	int		i;
	char	*cmd;

	i = -1;
	while (args[++i])
		;
	current_cmd->args = args;
	cmd = ft_strdup(*args);
	current_cmd->cmd = cmp_cmd(cmd);
	free(cmd);
}

static char	**fill_tab(t_list *l, char **d)
{
	int		i;
	char	*s;

	i = 0;
	while (l)
	{
		s = l->content;
		d[i++] = ft_strdup(s);
		l = l->next;
	}
	d[i] = 0;
	return (d);
}

static t_cmd_line	*create_redir_params(t_shell *sh, t_cmd_line *cmd_line)
{
	cmd_line->redir = (t_redir *)msh_malloc(1, sizeof(t_redir));
	cmd_line->redir->fd_o = sh->redir->fd_o;
	cmd_line->redir->fd_i = sh->redir->fd_i;
	cmd_line->redir->fd_n = sh->redir->fd_n;
	cmd_line->redir->id_o = sh->redir->id_o;
	cmd_line->redir->id_i = sh->redir->id_i;
	cmd_line->redir->id_n = sh->redir->id_n;
	cmd_line->redir->name_o = ft_strdup(sh->redir->name_o);
	cmd_line->redir->name_i = ft_strdup(sh->redir->name_i);
	cmd_line->redir->name_n = ft_strdup(sh->redir->name_n);
	return (cmd_line);
}

void	create_cmd_list(t_shell *sh)
{
	t_cmd_line	*cmd_line;

	cmd_line = NULL;
	cmd_line = (t_cmd_line *)msh_malloc(1, sizeof(t_cmd_line));
	init_cmd_line(&cmd_line);
	cmd_line->args = (char **)msh_malloc((ft_lstsize(sh->lst_arg) + 1), \
	sizeof(char *));
	cmd_line->args = fill_tab(sh->lst_arg, cmd_line->args);
	if (sh->redir)
		cmd_line = create_redir_params(sh, cmd_line);
	get_cmd_line(cmd_line, cmd_line->args);
	cmd_line->option_echo = sh->tmp_option_echo;
	ft_lstadd_back(&sh->cmd, ft_lstnew(cmd_line));
}
