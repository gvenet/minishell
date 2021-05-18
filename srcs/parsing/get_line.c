/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:28:35 by smorel            #+#    #+#             */
/*   Updated: 2021/03/05 10:28:36 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_prompt(void)
{
	write(2, "\033[36;01m", ft_strlen("\033[36;01m"));
	write(2, "BASH de coincoin : ", ft_strlen("BASH de coincoin : "));
	write(2, "\033[00m", ft_strlen("\033[00m"));
}

int	get_line(t_shell *sh)
{
	char			*buf;

	dup2(sh->fd_sav[0], STDIN_FILENO);
	dup2(sh->fd_sav[1], STDOUT_FILENO);
	init_termcap_msh(sh->t);
	ms_prompt();
	buf = termcap_pars(sh);
	write(STDOUT_FILENO, "\n", 1);
	reset_input_mode ();
	if (buf)
		pars_line(sh, buf);
	del_fct(&buf);
	return (E_SUCCESS);
}
