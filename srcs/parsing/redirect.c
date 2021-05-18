#include <minishell.h>

static int	file_creation_input(t_shell *sh, char *b_ptr, int n, int id)
{
	char	*path;

	if (sh->redir->fd_i >= 0)
	{
		free(sh->redir->name_i);
		close(sh->redir->fd_i);
	}
	sh->redir->id_i = id;
	sh->redir->name_i = fill_arg(sh, &b_ptr, sh->redir->name_i, n);
	path = file_path(sh->redir->name_i);
	sh->redir->fd_i = open(path, O_RDONLY, S_IRWXU);
	free(path);
	if (sh->redir->fd_i < 0)
	{	
		close(sh->redir->fd_i);
		return (E_FAIL);
	}
	return (E_SUCCESS);
}

static int	file_creation_output(t_shell *sh, char *b_ptr, int n, int id)
{
	char	*path;

	if (sh->redir->fd_o >= 0)
	{
		free(sh->redir->name_o);
		close(sh->redir->fd_o);
	}
	sh->redir->id_o = id;
	sh->redir->name_o = fill_arg(sh, &b_ptr, sh->redir->name_o, n);
	path = file_path(sh->redir->name_o);
	if (sh->redir->id_o == RAFTSUP)
		sh->redir->fd_o = open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	else if (sh->redir->id_o == DRAFTSUP)
		sh->redir->fd_o = open(path, O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
	free(path);
	if (sh->redir->fd_o < 0)
	{
		close(sh->redir->fd_o);
		return (E_FAIL);
	}
	return (E_SUCCESS);
}

static int	file_creation_n(t_shell *sh, char *b_ptr, int n, int id)
{
	char	*path;

	if (sh->redir->fd_n >= 0)
	{
		free(sh->redir->name_n);
		close(sh->redir->fd_n);
	}
	sh->redir->id_n = id;
	sh->redir->name_n = fill_arg(sh, &b_ptr, sh->redir->name_n, n);
	path = file_path(sh->redir->name_n);
	if (sh->redir->id_n == RAFTN)
		sh->redir->fd_n = open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	else if (sh->redir->id_n == DRAFTN)
		sh->redir->fd_n = open(path, O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
	free(path);
	if (sh->redir->fd_n < 0)
	{	
		close(sh->redir->fd_n);
		return (E_FAIL);
	}
	return (E_SUCCESS);
}

static int	file_creation_selector(t_shell *sh, char *b_ptr, int n, int id)
{
	if (id == RAFTSUP || id == DRAFTSUP)
	{
		if (file_creation_output(sh, b_ptr, n, id) == E_FAIL)
			return (E_FAIL);
	}
	else if (id == RAFTINF)
	{
		if (file_creation_input(sh, b_ptr, n, id) == E_FAIL)
			return (E_FAIL);
	}
	else if (id == RAFTN || id == DRAFTN)
	{
		if (file_creation_n(sh, b_ptr, n, id) == E_FAIL)
			return (E_FAIL);
	}
	else if (id == RAFTNP || id == DRAFTNP)
	{
		if (file_creation_np(sh, b_ptr, n, id) == E_FAIL)
			return (E_FAIL);
	}	
	return (E_SUCCESS);
}

int	analysis_redir(t_shell *sh, char **buf, int id)
{	
	int		n;
	char	*b_ptr;

	sh->redir_process_engaged = E_TRUE;
	init_redir(sh);
	*buf = trim_ws(*buf);
	b_ptr = *buf;
	n = analysis_arg(sh, buf);
	if (n == E_FAIL)
		return (E_FAIL);
	if (file_creation_selector(sh, b_ptr, n, id) == E_FAIL)
		return (E_FAIL);
	b_ptr = *buf;
	b_ptr = trim_ws(b_ptr);
	if (is_sep(*b_ptr))
		*buf = b_ptr;
	return (E_SUCCESS);
}
