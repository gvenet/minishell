/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:24:47 by smorel            #+#    #+#             */
/*   Updated: 2021/03/05 10:24:48 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *sh, void *a)
{
	char	*output;

	output = getcwd(NULL, 0);
	write(STDOUT_FILENO, output, ft_strlen(output));
	write(STDOUT_FILENO, "\n", 1);
	return (ret_exit(sh, 0, E_SUCCESS));
	(void)a;
}

int	ft_env(t_shell *sh, void *b)
{
	int	i;

	i = -1;
	while (sh->env[++i])
	{
		if (!ft_strchr(sh->env[i], '='))
			continue ;
		write(STDOUT_FILENO, sh->env[i], ft_strlen(sh->env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (ret_exit(sh, 0, E_SUCCESS));
	(void)b;
}

int	ft_echo(t_shell *sh, void *cm)
{
	t_cmd_line	*cmd;
	int			i;
	int			len;

	cmd = cm;
	len = -1;
	while (cmd->args[++len])
		;
	i = 0;
	if (len == 1 && !cmd->option_echo)
		write(STDOUT_FILENO, "\n", 1);
	while (cmd->args[++i])
	{
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		if (--len > 1)
			write(STDOUT_FILENO, " ", 1);
		else if (!cmd->option_echo)
			write(STDOUT_FILENO, "\n", 1);
	}
	return (ret_exit(sh, 0, E_SUCCESS));
}

int	ft_cd(t_shell *sh, void *cmd)
{
	int		ret;
	char	*val;

	ft_set_oldpwd(sh, 1);
	val = ((t_cmd_line *)cmd)->args[1];
	if (val == NULL)
		return (ft_cd_val_null(sh, val));
	ret = 0;
	if (chdir(val) == -1 && *val != 0)
	{
		write(STDERR_FILENO, val, ft_strlen(val));
		write(STDERR_FILENO, ": No such file or directory\n", \
		ft_strlen(": No such file or directory\n"));
		ft_set_oldpwd(sh, 0);
		ret = 1;
	}
	else
		ft_set_pwd(sh, getcwd(NULL, 0));
	if (((t_cmd_line *)cmd)->args[1] == NULL)
		del_fct(&val);
	return (ret_exit(sh, ret, E_SUCCESS));
}

int	ft_nomatch(t_shell *sh, void *cmd)
{
	int	code;

	code = test_cmd(sh, (t_cmd_line *)cmd, 1, 0);
	signal(SIGINT, fc_cc);
	signal(SIGQUIT, SIG_IGN);
	return (ret_exit(sh, code, E_SUCCESS));
}
