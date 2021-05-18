#include "minishell.h"

int	str_digit(char *str)
{
	if (!str)
		return (E_SUCCESS);
	if (*str == '-' || *str == '+')
		str++;
	while (*str && str)
	{
		if (ft_isdigit(*str))
			str++;
		else
		{
			return (E_FAIL);
			break ;
		}
	}
	return (E_SUCCESS);
}

static void	export_algo_normy(t_shell *sh, t_export *v)
{
	v->var_to_set = ft_strdup(v->vars[v->i[0]]);
	v->split = ft_split(v->var_to_set, '=');
	ft_unset_algo(sh, v->split[0]);
	v->split = ft_strdel_2d(v->split);
	v->i[1] = ft_strlen_2d(v->new_env);
	v->new_env[v->i[1]] = v->var_to_set;
	v->new_env[v->i[1] + 1] = NULL;
}

int	export_algo(t_shell *sh, void *cmd)
{
	int			ret;
	t_export	v;

	ret = 0;
	v.vars = ((t_cmd_line *)cmd)->args;
	v.i[1] = ft_strlen_2d(sh->env) + ft_strlen_2d(v.vars);
	v.new_env = (char **)malloc(sizeof(char *) * v.i[1]);
	v.i[0] = -1;
	while (sh->env[++v.i[0]])
		v.new_env[v.i[0]] = ft_strdup(sh->env[v.i[0]]);
	v.new_env[v.i[0]] = NULL;
	sh->env = ft_strdel_2d(sh->env);
	sh->env = v.new_env;
	v.i[0] = 0;
	while (v.vars[++v.i[0]])
	{
		if (check_export_name(v.vars[v.i[0]]) == E_FAIL)
			ret = 1;
		else
			export_algo_normy(sh, &v);
	}
	return (ret);
}

int	ft_cd_val_null(t_shell *sh, char *val)
{
	int		ret;

	ret = f_getenv("HOME", sh, &val);
	if (ret == E_FAIL)
	{
		write(STDERR_FILENO, "cd: HOME not set\n", \
		ft_strlen("cd: HOME not set\n"));
		return (ret_exit(sh, 1, E_FAIL));
	}
	chdir(val);
	ft_set_pwd(sh, val);
	return (ret_exit(sh, 0, E_SUCCESS));
}
