#include <minishell.h>

static int	check_end(char *buf)
{
	buf = trim_ws(buf);
	if (is_sep(*buf) || *buf == 0)
		return (1);
	return (0);
}

static int	raftsup_selector(char **buf, int r1, int r2)
{
	(*buf)++;
	if (**buf == '>')
	{
		(*buf)++;
		if (**buf == '>' || **buf == '<' || check_end(*buf))
			return (E_FAIL);
		return (r1);
	}
	else if (**buf == '<' || check_end(*buf))
		return (E_FAIL);
	return (r2);
}

static int	raftn(char **buf, int i)
{
	int			j;
	char		*nptr;
	long long	fd;

	j = 0;
	nptr = (char *)msh_malloc(i + 1, sizeof(char));
	while (j < i)
		nptr[j++] = *(*buf)++;
	fd = ft_atoi(nptr);
	free(nptr);
	if (fd > 255)
		return (E_FAIL);
	if (fd == 1)
		return (raftsup_selector(buf, DRAFTSUP, RAFTSUP));
	else if (fd == 2)
		return (raftsup_selector(buf, DRAFTN, RAFTN));
	else if (fd == 0 || fd > 2)
		return (raftsup_selector(buf, DRAFTNP, RAFTNP));
	return (E_NO_MATCH);
}

int	is_redir(t_shell *sh, char **buf)
{
	int	i;

	if (ft_isdigit(**buf) && sh->pars_char == E_FALSE)
	{
		i = 0;
		while (ft_isdigit((*buf)[i]))
		{
			i++;
			if ((*buf)[i] == '>')
				return (raftn(buf, i));
		}
	}
	if (**buf == '>')
		return (raftsup_selector(buf, DRAFTSUP, RAFTSUP));
	else if (**buf == '<')
	{
		(*buf)++;
		if (**buf == '<' || **buf == '>' || check_end(*buf))
			return (E_FAIL);
		return (RAFTINF);
	}
	else
		return (E_NO_MATCH);
}

int	file_creation_np(t_shell *sh, char *b_ptr, int n, int id)
{
	char	*path;
	char	*flag;
	int		fd;

	fd = -1;
	flag = NULL;
	flag = fill_arg(sh, &b_ptr, flag, n);
	path = file_path(flag);
	free(flag);
	if (id == RAFTNP)
		fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	else if (id == DRAFTNP)
		fd = open(path, O_CREAT | O_APPEND | O_WRONLY, S_IRWXU);
	free(path);
	if (fd < 0)
	{	
		close(fd);
		return (E_FAIL);
	}
	close(fd);
	return (E_SUCCESS);
}
