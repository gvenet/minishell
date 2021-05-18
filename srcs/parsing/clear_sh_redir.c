#include <minishell.h>

void	clear_sh_redir(t_shell *sh)
{
	if (sh->redir)
	{
		free(sh->redir->name_i);
		sh->redir->name_i = NULL;
		free(sh->redir->name_n);
		sh->redir->name_n = NULL;
		free(sh->redir->name_o);
		sh->redir->name_o = NULL;
		free(sh->redir);
		sh->redir = NULL;
	}
}
