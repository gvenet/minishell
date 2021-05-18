/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:24:25 by smorel            #+#    #+#             */
/*   Updated: 2021/03/05 10:24:26 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// SIG_IGN	signal is ignored
int	main(int argc, char **argv, char **env)
{
	t_shell	*sh;

	sh = (t_shell *)msh_malloc(1, sizeof(t_shell));
	init_sh(argc, argv, env, sh);
	signal(SIGINT, fc_cc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		get_line(sh);
	return (sh->exit);
}
