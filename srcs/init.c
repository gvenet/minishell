/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:25:08 by smorel            #+#    #+#             */
/*   Updated: 2021/03/05 12:25:09 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_line(t_cmd_line **cmd_line)
{
	(*cmd_line)->cmd = E_NO_MATCH;
	(*cmd_line)->option_echo = 0;
	(*cmd_line)->args = NULL;
	(*cmd_line)->redir = NULL;
	(*cmd_line)->redir_pipe = 0;
}

static void	init_env(char **env, t_shell *sh)
{
	int	i;

	i = ft_strlen_2d(env);
	sh->env = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (env[++i])
		sh->env[i] = ft_strdup(env[i]);
	sh->env[i] = ft_strdup("OLDPWD");
	i++;
	sh->env[i] = NULL;
}

void	init_sh(int argc, char **argv, char **env, t_shell *sh)
{
	sh->fd_sav[0] = dup(STDIN_FILENO);
	sh->fd_sav[1] = dup(STDOUT_FILENO);
	sh->exit = 0;
	init_env(env, sh);
	sh->cmd = NULL;
	sh->lst_arg = NULL;
	sh->redir = NULL;
	sh->t = (t_term *)malloc(sizeof(t_term));
	sh->hist.history = (char **)ft_memalloc(sizeof(char *) * (HISTSIZE + 1));
	(void)argc;
	(void)argv;
}

void	init_redir(t_shell *sh)
{
	if (sh->redir == NULL)
	{
		sh->redir = (t_redir *)msh_malloc(1, sizeof(t_redir));
		sh->redir->id_o = 0;
		sh->redir->fd_o = -1;
		sh->redir->name_o = NULL;
		sh->redir->id_i = 0;
		sh->redir->fd_i = -1;
		sh->redir->name_i = NULL;
		sh->redir->id_n = 0;
		sh->redir->fd_n = -1;
		sh->redir->name_n = NULL;
	}
}
