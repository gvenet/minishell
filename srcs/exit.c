/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:25:14 by smorel            #+#    #+#             */
/*   Updated: 2021/03/05 12:25:16 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_malloc_fail(void)
{
	exit(1);
}

void	free_shell(t_shell *sh, unsigned int code_err)
{
	sh->env = ft_strdel_2d(sh->env);
	clear_lst_cmd(&sh->cmd);
	sh->hist.history = ft_strdel_2d(sh->hist.history);
	ret_exit(sh, code_err, code_err);
	ft_close_pipe(sh->fd_sav);
	exit(code_err);
}
