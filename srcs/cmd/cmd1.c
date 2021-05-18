/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:24:40 by smorel            #+#    #+#             */
/*   Updated: 2021/03/05 10:24:41 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// https://tldp.org/LDP/abs/html/exitcodes.html#exitCODESREF

static void	definitiv_exit(t_shell *sh, void *cmd)
{
	char				*str;

	str = ((t_cmd_line *)cmd)->args[1];
	write(STDERR_FILENO, "exit: ", ft_strlen("exit: "));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	free_shell(sh, -1);
}

int	ft_exit(t_shell *sh, void *cmd)
{
	long long int		code_err;
	int					check_digit_only;

	code_err = sh->exit;
	write(STDERR_FILENO, "exit\n", 5);
	check_digit_only = str_digit(((t_cmd_line *)cmd)->args[1]);
	if (check_digit_only == E_FAIL)
		definitiv_exit(sh, cmd);
	if (((t_cmd_line *)cmd)->args[1])
		ft_atoi_msh(((t_cmd_line *)cmd)->args[1], &code_err);
	code_err %= 256;
	if (code_err < 0)
		code_err += 256;
	if (((t_cmd_line *)cmd)->args[2] && ((t_cmd_line *)cmd)->args[1])
	{
		write(STDERR_FILENO, "exit: too many arguments\n", 25);
		code_err = 1;
	}
	free_shell(sh, code_err);
	return (ret_exit(sh, 0, E_SUCCESS));
}

void	ft_unset_algo(t_shell *sh, char *var_to_unset)
{
	int	len;
	int	i;

	i = -1;
	len = ft_strlen(var_to_unset);
	while (sh->env[++i])
	{
		if (!ft_strncmp(sh->env[i], var_to_unset, len))
		{
			del_fct(&sh->env[i]);
			while (sh->env[i + 1])
			{
				sh->env[i] = ft_strdup(sh->env[i + 1]);
				del_fct(&sh->env[++i]);
			}
		}
	}
}

int	ft_unset(t_shell *sh, void *cmd)
{
	char	*var_to_unset;
	int		i;

	i = 0;
	while (((t_cmd_line *)cmd)->args[++i])
	{
		var_to_unset = ((t_cmd_line *)cmd)->args[i];
		if (f_getenv(var_to_unset, sh, NULL) != E_FAIL)
		{
			if (ft_strncmp("_", var_to_unset, 1))
				ft_unset_algo(sh, var_to_unset);
		}
		else if (ft_isdigit(*var_to_unset) || !str_alnum(var_to_unset))
		{
			write(STDERR_FILENO, "unset: `", ft_strlen("unset: `"));
			write(STDERR_FILENO, var_to_unset, ft_strlen(var_to_unset));
			write(STDERR_FILENO, "': not a valid identifier\n", \
			ft_strlen("': not a valid identifier\n"));
			return (ret_exit(sh, 1, E_FAIL));
		}
	}
	return (ret_exit(sh, 0, E_SUCCESS));
}
