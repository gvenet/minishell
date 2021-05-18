#include <minishell.h>

static void	clear_cmd_line_redir(t_cmd_line **cmd_line)
{
	if ((*cmd_line)->redir)
	{
		free((*cmd_line)->redir->name_o);
		(*cmd_line)->redir->name_o = NULL;
		free((*cmd_line)->redir->name_n);
		(*cmd_line)->redir->name_n = NULL;
		free((*cmd_line)->redir->name_i);
		(*cmd_line)->redir->name_i = NULL;
		free((*cmd_line)->redir);
		(*cmd_line)->redir = NULL;
	}
}

static void	clear_cmd_line_args(t_cmd_line **cmd_line)
{
	int	i;

	i = -1;
	while ((*cmd_line)->args[++i])
	{
		free((*cmd_line)->args[i]);
		(*cmd_line)->args[i] = NULL;
	}
	free((*cmd_line)->args);
	(*cmd_line)->args = NULL;
}

void	clear_lst_cmd(t_list **lst)
{
	t_list		*tmp;
	t_cmd_line	*cmd_line;

	while (*lst)
	{
		tmp = (*lst)->next;
		if (*lst)
		{
			cmd_line = (t_cmd_line *)(*lst)->content;
			clear_cmd_line_args(&cmd_line);
			clear_cmd_line_redir(&cmd_line);
			free(cmd_line);
			cmd_line = NULL;
			free(*lst);
		}
		*lst = tmp;
	}
	*lst = NULL;
}
